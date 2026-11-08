"""Validate a private Korean-layout save produced by localized Clean gameplay.

Checks both town banks, their setup markers, checksums and the first player's names.
No save data is modified. This checks storage integrity; loading in the game is a
separate gameplay check.
"""
from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path
import struct

SAVE_SIZE = 0x40000
BANK_SIZE = 0x173FC
CHECKSUM = 0x173F8
TOWN_NAME = 4
PLAYER_NAME = 0x14 + 0x247E + 0x10


def name_at(bank: bytes, offset: int) -> str:
    return bank[offset:offset + 12].decode("utf-16le").split("\0", 1)[0]


def validate(data: bytes, player: str, town: str) -> dict:
    if len(data) != SAVE_SIZE:
        raise ValueError(f"expected {SAVE_SIZE} save bytes, got {len(data)}")
    banks = []
    for number in range(2):
        bank = data[number * BANK_SIZE:(number + 1) * BANK_SIZE]
        if bank[0] != 0x32:
            raise ValueError(f"bank {number}: town has not been set up")
        if sum(struct.unpack(f"<{BANK_SIZE // 2}H", bank)) & 0xFFFF:
            raise ValueError(f"bank {number}: invalid checksum")
        if name_at(bank, PLAYER_NAME) != player or name_at(bank, TOWN_NAME) != town:
            raise ValueError(f"bank {number}: stored names differ from the expected names")
        banks.append({"bank": number, "checksum_valid": True, "names_match": True})
    return {"size": len(data), "sha256": hashlib.sha256(data).hexdigest(), "banks": banks}


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("save", type=Path)
    ap.add_argument("--player", required=True, help="the first player's exact name")
    ap.add_argument("--town", required=True, help="the town's exact name")
    args = ap.parse_args()
    try:
        report = validate(args.save.read_bytes(), args.player, args.town)
    except (ValueError, OSError, UnicodeError) as exc:
        ap.error(str(exc))
    print(json.dumps(report))


if __name__ == "__main__":
    main()
