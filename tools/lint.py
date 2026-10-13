"""Checks that need neither the ROM nor the compiler, so CI can run them.

    python tools/lint.py

Checks the source headers and paths against config/, duplicate addresses, files that must
not be committed, and that every text file is English only (game text is written as byte
escapes, e.g. "\xb0\xa1").
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
        m = HANGUL.search(text)
        if m:
            line = text.count("\n", 0, m.start()) + 1
            errors.append(f"{rel}:{line}: Hangul text; the repository is English-only")

    for e in errors[:50]:
        print(e)
    if len(errors) > 50:
        print(f"... and {len(errors) - 50} more")
    print(f"{len(sources)} sources, {len(errors)} problems")
    sys.exit(1 if errors else 0)


if __name__ == "__main__":
    main()
