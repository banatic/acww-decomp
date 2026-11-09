"""tools/match_version.py's helpers on made-up words (no game bytes): call decoding, the
relocation module names, the masks, the order filter and ds-decomp's module hash."""
from __future__ import annotations

import pathlib
import struct
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import match_version as M  # noqa: E402


def thumb_bl(at: int, to: int, blx: bool = False) -> bytes:
    off = (to - ((at + 4) & ~3 if blx else at + 4)) & 0x7FFFFF
    return struct.pack("<HH", 0xF000 | (off >> 12) & 0x7FF, (0xE800 if blx else 0xF800) | (off >> 1) & 0x7FF)


def arm_bl(at: int, to: int) -> bytes:
    return struct.pack("<I", 0xEB000000 | ((to - at - 8) >> 2) & 0xFFFFFF)


def main() -> int:
    problems = []
    checks = [0]

    def expect(what: str, got, want) -> None:
        checks[0] += 1
        if got != want:
            problems.append(f"{what}: {got!r}, expected {want!r}")

    expect("thumb BL forward", M.call_target("thumb_call", thumb_bl(0x02000100, 0x02010000), 0x02000100), 0x02010000)
    expect("thumb BL back", M.call_target("thumb_call", thumb_bl(0x02010002, 0x02000000), 0x02010002), 0x02000000)
    expect("thumb BLX", M.call_target("thumb_call_arm", thumb_bl(0x02000102, 0x02000400, True), 0x02000102),
           0x02000400)
    expect("ARM BL", M.call_target("arm_call", arm_bl(0x02000100, 0x01FF8000), 0x02000100), 0x01FF8000)
    expect("not a call", M.call_target("thumb_call", b"\0\0\0\0", 0x02000000), None)
    expect("one overlay", M.target_modules("overlay(5)"), ["ov005"])
    expect("overlays", M.target_modules("overlays(94,147)"), ["ov094", "ov147"])
    expect("autoload", M.target_modules("autoload(2)"), ["autoload_2"])
    expect("main", M.target_modules("main"), ["main"])
    expect("none", M.target_modules("none"), [])
    expect("masked", M.masked(b"abcdefghij", [2]), b"ab\0\0\0\0ghij")
    expect("masked at the end", M.masked(b"abcdef", [4]), b"abcd\0\0")
    expect("longest run", M.longest_run(32, [4, 20]), (8, 12))
    expect("longest run, none masked", M.longest_run(10, []), (0, 10))
    s = [M.Sym(f"f{i}", "function", i, 2, True, "", "", "") for i in range(6)]
    rows = list(zip(s, [10, 20, 5, 30, 40, 35]))
    expect("order filter", [a for _, a in M.lis(rows)], [10, 20, 30, 35])
    expect("hash of nothing", M.module_hash(b""), 0)
    expect("hash differs by length", M.module_hash(b"\0") != M.module_hash(b"\0\0"), True)
    for line in problems:
        print(line)
    print(f"{checks[0] - len(problems)} of {checks[0]} matching checks pass")
    return 1 if problems else 0


if __name__ == "__main__":
    sys.exit(main())
