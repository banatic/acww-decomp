"""Prepare an explicit shop/fishing/letter fixture from a private localized test save.

This is scenario setup, not evidence of completing Nook's job or obtaining tools in play.
The input is never changed; the output must be a new file.
"""
from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path
import struct

import check_localized_save as S


def prepare(data: bytes) -> tuple[bytes, dict]:
    if len(data) != S.SAVE_SIZE:
        raise ValueError("expected a full 256 KiB save chip")
    S.validate(data, S.name_at(data, S.PLAYER_NAME), S.name_at(data, S.TOWN_NAME))
    bank = bytearray(data[:S.BANK_SIZE])
    flags_at = 0x14 + 0x23F8
    flags, = struct.unpack_from("<I", bank, flags_at)
    patches = [(flags_at, "<I", flags & ~2, "Nook job inactive"),
               (0x1C24, "<I", 10000, "wallet"),
               (0x241A, "<H", 0x1374, "held fishing rod"),
               (0x1C06, "<H", 0x1518, "apple in pocket 0"),
               (0x1C08, "<H", 0x1020, "paper in pocket 1")]
    changes = []
    for at, fmt, value, purpose in patches:
        before, = struct.unpack_from(fmt, bank, at)
        struct.pack_into(fmt, bank, at, value)
        changes.append({"offset": hex(at), "format": fmt, "before": before, "after": value, "purpose": purpose})
    struct.pack_into("<H", bank, S.CHECKSUM, 0)
    struct.pack_into("<H", bank, S.CHECKSUM, -sum(struct.unpack(f"<{S.BANK_SIZE // 2}H", bank)) & 0xFFFF)
    result = bytes(bank) * 2 + data[2 * S.BANK_SIZE:]
    S.validate(result, S.name_at(data, S.PLAYER_NAME), S.name_at(data, S.TOWN_NAME))
    return result, {"source_sha256": hashlib.sha256(data).hexdigest(),
                    "output_sha256": hashlib.sha256(result).hexdigest(), "changes_in_each_bank": changes}


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("source", type=Path)
    ap.add_argument("output", type=Path)
    args = ap.parse_args()
    try:
        result, report = prepare(args.source.read_bytes())
        with args.output.open("xb") as out:
            out.write(result)
    except (OSError, ValueError, UnicodeError) as exc:
        ap.error(str(exc))
    print(json.dumps(report))


if __name__ == "__main__":
    main()
