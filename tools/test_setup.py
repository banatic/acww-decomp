"""tools/setup.py's ROM checks on made-up headers (no game bytes): what each kind of wrong file
is told."""
from __future__ import annotations

import pathlib
import struct
import sys
import tempfile

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import setup  # noqa: E402


def header(title: bytes, code: bytes, revision: int = 0, good_crc: bool = True) -> bytes:
    h = bytearray(0x200)
    h[0:12] = title.ljust(12, b"\0")
    h[12:16] = code
    h[0x1E] = revision
    crc = setup.header_crc(bytes(h))
    struct.pack_into("<H", h, 0x15E, crc if good_crc else crc ^ 1)
    return bytes(h)


def told(data: bytes) -> str:
    with tempfile.TemporaryDirectory() as d:
        path = pathlib.Path(d) / "game.nds"
        path.write_bytes(data)
        try:
            setup.check_rom(path)
        except SystemExit as e:
            return str(e)
    return "accepted"


CASES = [
    (b"x" * 16, "not a DS ROM"),
    (header(b"ANIMAL CROSS", b"ADMK", good_crc=False), "checksum is wrong"),
    (header(b"POKEMON D", b"ADAE"), "not Animal Crossing"),
    (header(b"ANIMAL CROSS", b"ADME"), "North America release"),
    (header(b"ANIMAL CROSS", b"ADMJ"), "Japan release"),
    (header(b"ANIMAL CROSS", b"ADMK", revision=1), "revision 1"),
    (header(b"ANIMAL CROSS", b"ADMK"), "a bad or modified dump"),
]


def main() -> int:
    bad = 0
    for data, want in CASES:
        got = told(data)
        if want not in got:
            bad += 1
            print(f"FAIL: expected '{want}', got: {got}")
    print(f"{len(CASES) - bad} of {len(CASES)} ROM checks say what is wrong")
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
