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
    names: dict[str, pathlib.Path] = {}
    sources = C.all_sources()
    functions = 0
    for path in sources:
        rel = path.relative_to(C.ROOT).as_posix()
        srcs = C.parse_sources(path)
        if not srcs:
            errors.append(f"{rel}: missing or malformed header")
            continue
        functions += len(srcs)
        parts = rel.split("/")
        if not ((parts[0] == "src" and len(parts) == 3) or
                (parts[0] == "libs" and len(parts) == 4 and parts[1] in LIB_PACKAGES)):
            errors.append(f"{rel}: not at src/<module>/ or libs/<Package>/<module>/")
        if path.parent.name != srcs[0].module:
            errors.append(f"{rel}: header says module {srcs[0].module}")
        unit = C.UNIT_HEADER.match(path.read_text(encoding="utf-8", errors="replace"))
        if unit is None and path.stem not in (srcs[0].name, f"{srcs[0].name}__{srcs[0].module}_{srcs[0].address:08x}"):
            errors.append(f"{rel}: file name does not match header symbol {srcs[0].name}")
        if unit is not None:
            # a unit (several functions, one original source file): named for what it is, its
            # functions listed last address first (common.UNIT_HEADER), as many as the first line
            # says, all of them ARM or all Thumb (the compiler's -thumb is one per file), and
            # defined in the file in that order
            if path.stem != unit["unit"]:
                errors.append(f"{rel}: file name does not match the unit's name {unit['unit']}")
            if int(unit["count"]) != len(srcs) or len(srcs) < 2:
                errors.append(f"{rel}: the header lists {len(srcs)} functions, not {unit['count']}"
                              if len(srcs) > 1 else f"{rel}: a unit of one function; give it the one-function header")
            if [s.address for s in srcs] != sorted({s.address for s in srcs}, reverse=True):
                errors.append(f"{rel}: the unit's functions are not listed last address first")
            if len({s.thumb for s in srcs}) > 1:
                errors.append(f"{rel}: the unit mixes ARM and Thumb functions")
            body = path.read_text(encoding="utf-8", errors="replace")
            body = body[C.header_end(body):]
            # each definition: at the start of a line, its name, its parameters and the brace
            at = [C.unit_definition(body, s.name) for s in srcs]
            for name in C.undeclared_uses(body, [s.name for s in srcs]):
                errors.append(f"{rel}: {name} is used before it is declared; give it a prototype above")
            for s, m in zip(srcs, at):
                if m is None:
                    errors.append(f"{rel}: {s.name} is listed but not defined")
            if all(at) and [m.start() for m in at] != sorted(m.start() for m in at):
                errors.append(f"{rel}: the unit defines its functions in another order than it lists them")
        # dsd names each object for its source file and refuses a file name two modules use
        if path.name in names and names[path.name] != path.parent:
            errors.append(f"{rel}: {names[path.name].relative_to(C.ROOT).as_posix()} has the same file name; "
                          "dsd needs one per file")
        names.setdefault(path.name, path.parent)
        for src in srcs:
            sym = syms.function(src.module, src.address)
            if sym is None or sym.size != src.size:
                errors.append(f"{rel}: no {src.size:#x}-byte function at {src.address:#010x}")
            key = (src.module, src.address)
            if key in seen:
                errors.append(f"{rel}: same address as {seen[key].relative_to(C.ROOT).as_posix()}")
            seen[key] = path

    # runtime/native-private.txt (tools/link.py) and the Native tables name functions by their
    # keys (common.function_key): each must still be a function of a source
    present = {C.function_key(s) for p in sources for s in C.parse_sources(p)}
    for rel in sorted(set(C.read_native_private()) - present):
        errors.append(f"{C.NATIVE_PRIVATE.relative_to(C.ROOT).as_posix()}: {rel} is not a function of a source; "
                      "run tools/link.py")
    # (each pinned by the digest of its own text: a change to the function needs a new audit)
    import native_tables
    for table, key, digest in native_tables.pinned():
        defined = C.function_source(key) if key in present else None
        if defined is None:
            errors.append(f"{table}: {key} is not a function of a source")
        elif digest is not None and C.pinned_sha256(key, defined.path.read_text(encoding="utf-8")) != digest:
            errors.append(f"{table}: {key} changed since its audit (tools/native_tables.py)")

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
    print(f"{len(sources)} sources ({functions} functions), {len(errors)} problems")
    sys.exit(1 if errors else 0)


if __name__ == "__main__":
    main()
