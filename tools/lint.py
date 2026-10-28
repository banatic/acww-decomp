"""Checks that need neither the ROM nor the compiler, so CI can run them.

    python tools/lint.py

Checks the source headers and paths against config/, duplicate addresses, files that must
not be committed, that every text file is English only (game text is written as byte
escapes, e.g. "\xb0\xa1"), and that no unreachable group of docs/scene-plan-groups.txt takes a
Clean function the committed scenes enter (runtime/recordings/scenes/clean-entered.txt).
"""

from __future__ import annotations

import pathlib
import re
import subprocess
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import common as C  # noqa: E402

FORBIDDEN_SUFFIXES = {".nds", ".sav", ".bin", ".o", ".exe", ".dll"}
LIB_PACKAGES = {"NitroSDK", "NitroSystem", "NitroDWC", "NitroWiFi", "GameSpy", "MSL", "Runtime"}
# Hangul jamo, compatibility jamo, extended jamo A/B and syllables, by code point so this
# file itself contains none.
HANGUL_RANGES = ((0x1100, 0x11FF), (0x3130, 0x318F), (0xA960, 0xA97F), (0xAC00, 0xD7FF))
HANGUL = re.compile("[" + "".join(f"{chr(a)}-{chr(b)}" for a, b in HANGUL_RANGES) + "]")


def tracked_or_present() -> list[pathlib.Path]:
    try:
        out = subprocess.run(["git", "ls-files", "--cached", "--others", "--exclude-standard"],
                             cwd=C.ROOT, capture_output=True, text=True, check=True).stdout
        return [C.ROOT / line for line in out.splitlines() if line]
    except (OSError, subprocess.CalledProcessError):
        return [p for p in C.ROOT.rglob("*") if p.is_file() and ".git" not in p.parts]


def macro_shadows() -> list[str]:
    """A Clean file's #define named like an enumerator of a header it includes replaces that
    constant everywhere after it without a warning: room_villager.c's offset of the talk scene,
    ROOM_VILLAGER_TALK (0x680), stood in for the state ROOM_VILLAGER_TALK (1)."""
    include = re.compile(r'^\s*#\s*include\s+"([^"]+)"', re.M)
    enum = re.compile(r"\benum\b[^{;]*\{(.*?)\}", re.S)
    define = re.compile(r"^[ \t]*#[ \t]*define[ \t]+([A-Za-z_]\w*)\b", re.M)
    cache: dict[pathlib.Path, tuple[list[pathlib.Path], set[str]]] = {}

    def parse(path: pathlib.Path) -> tuple[list[pathlib.Path], set[str]]:
        if path not in cache:
            text = path.read_text(encoding="utf-8", errors="replace")
            found = []
            for name in include.findall(text):
                for base in (path.parent, C.ROOT / "clean", C.INCLUDE):
                    if (base / name).is_file():
                        found.append((base / name).resolve())
                        break
            names = set()
            for m in enum.finditer(text):
                body = re.sub(r"/\*.*?\*/|//[^\n]*", "", m.group(1), flags=re.S)
                names.update(re.findall(r"(?:^|,)\s*([A-Za-z_]\w*)\s*(?==|,|$)", body.strip()))
            cache[path] = (found, names)
        return cache[path]

    errors = []
    for p in sorted((C.ROOT / "clean").rglob("*.c")):
        seen, todo, enumerators = set(), list(parse(p.resolve())[0]), {}
        while todo:
            header = todo.pop()
            if header in seen:
                continue
            seen.add(header)
            found, names = parse(header)
            todo += found
            for name in names:
                enumerators.setdefault(name, header)
        text = p.read_text(encoding="utf-8", errors="replace")
        for m in define.finditer(text):
            if m.group(1) in enumerators:
                line = text.count("\n", 0, m.start()) + 1
                errors.append(f"{p.relative_to(C.ROOT).as_posix()}:{line}: #define {m.group(1)} replaces the "
                              f"enumerator of {enumerators[m.group(1)].relative_to(C.ROOT).as_posix()}")
    return errors


def main() -> None:
    errors: list[str] = []
    mods = sorted(p.name for p in (C.CONFIG / "overlays").iterdir()) + list(C.RESIDENT)
    syms = C.SymbolTable({m: {} for m in mods})
    seen: dict[tuple[str, int], pathlib.Path] = {}
    sources = C.all_sources()
    for path in sources:
        rel = path.relative_to(C.ROOT).as_posix()
        src = C.parse_source(path)
        if src is None:
            errors.append(f"{rel}: missing or malformed header")
            continue
        parts = rel.split("/")
        if not ((parts[0] == "src" and len(parts) == 3) or
                (parts[0] == "libs" and len(parts) == 4 and parts[1] in LIB_PACKAGES)):
            errors.append(f"{rel}: not at src/<module>/ or libs/<Package>/<module>/")
        if path.parent.name != src.module:
            errors.append(f"{rel}: header says module {src.module}")
        if path.stem not in (src.name, f"{src.name}__{src.module}_{src.address:08x}"):
            errors.append(f"{rel}: file name does not match header symbol {src.name}")
        sym = syms.function(src.module, src.address)
        if sym is None or sym.size != src.size:
            errors.append(f"{rel}: no {src.size:#x}-byte function at {src.address:#010x}")
        key = (src.module, src.address)
        if key in seen:
            errors.append(f"{rel}: same address as {seen[key].relative_to(C.ROOT).as_posix()}")
        seen[key] = path

    for p in tracked_or_present():
        rel = p.relative_to(C.ROOT).as_posix()
        if p.suffix.lower() in FORBIDDEN_SUFFIXES or "mwccarm" in p.parts:
            errors.append(f"{rel}: must not be in the repository")
            continue
        try:
            raw = p.read_bytes()
            text = raw.decode("utf-8")
        except (UnicodeDecodeError, OSError):
            continue
        if b"\r" in raw:
            errors.append(f"{rel}: CRLF line endings; use LF")
        if rel.startswith("clean/") and not text.isascii():
            line = text.count("\n", 0, next(i for i, ch in enumerate(text) if not ch.isascii())) + 1
            errors.append(f"{rel}:{line}: non-ASCII text; Clean code is plain ASCII")
        m = HANGUL.search(text)
        if m:
            line = text.count("\n", 0, m.start()) + 1
            errors.append(f"{rel}:{line}: Hangul text; the repository is English-only")

    # Clean code is linked in one program that lets a name be defined twice (the Native objects
    # need that), so a second Clean function of the same name would silently replace the first.
    definition = re.compile(r"^(?!static\b)[A-Za-z_][\w \*]*?\b([A-Za-z_]\w*)\([^;{]*\)\n\{", re.M)
    defined: dict[str, str] = {}
    for p in sorted((C.ROOT / "clean").rglob("*.c")):
        rel = p.relative_to(C.ROOT).as_posix()
        for m in definition.finditer(p.read_text(encoding="utf-8", errors="replace")):
            if m.group(1) in defined and defined[m.group(1)] != rel:
                errors.append(f"{rel}: {m.group(1)} is also defined in {defined[m.group(1)]}")
            defined.setdefault(m.group(1), rel)

    errors += macro_shadows()

    # An unreachable group of the scene plan must not take a function a committed scene enters.
    import coverage  # noqa: PLC0415
    errors += coverage.unreachable_ran(syms)

    for e in errors[:50]:
        print(e)
    if len(errors) > 50:
        print(f"... and {len(errors) - 50} more")
    print(f"{len(sources)} sources, {len(errors)} problems")
    sys.exit(1 if errors else 0)


if __name__ == "__main__":
    main()
