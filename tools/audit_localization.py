"""Explain localization compatibility without exporting game text or guessing unused code.

    python tools/audit_localization.py --european EUROPE.nds --language es

The metadata-only report goes under build/localized-clean/audit-<language>.json.
"""
from __future__ import annotations

import argparse
from collections import Counter
import hashlib
import json
from pathlib import Path

import localize_clean as L

TEST_ACTOR_ARCHIVE = "/script/KOR/message/sp/npc/test_.bmg"


def usage(path: str) -> tuple[str, dict | None]:
    if path == TEST_ACTOR_ARCHIVE:
        return "documented unreachable from the retail Korean spawner", {
            "document": "docs/scene-plan-groups.txt (npc_plc)", "profile": "0x7c",
            "profile_address": "0x020e82f8", "spawner_table": "0x020e1d8c",
            "note": "The profile is absent from the spawner table and the plan records no code constructing it; "
                    "manually driven calls are a separate case."}
    return "not established by this static audit", None


def classify(korean: bytes, european: bytes, shared_across_languages: bool, string_file: bool) -> str:
    base_shape = L.bmg_shape(korean)
    donor_shape = L.bmg_shape(european)
    if korean[0x10] == 3 and shared_across_languages:
        return "shared_legacy_archive"
    if european[0x10] != 1 or korean[0x10] != 2:
        return "unsupported_encoding"
    if base_shape[1:] == donor_shape[1:]:
        return "importable"
    if string_file and L.empty_tail_compatible(korean, european):
        return "importable_empty_string_tail"
    return "message_index_mapping_required"


def audit(korean: bytes, european: bytes, language: str) -> dict:
    if hashlib.sha1(korean).hexdigest() != L.KR_SHA1 or hashlib.sha1(european).hexdigest() != L.EU_SHA1:
        raise ValueError("both ROMs must match the supported Korean and European SHA-1 values")
    if language not in L.LANGUAGES:
        raise ValueError("unsupported language")
    base, donor = L.Rom(korean), L.Rom(european)
    rows = []
    for path, file in sorted(base.files.items()):
        if not path.startswith("/script/KOR/"):
            continue
        suffix = path[len("/script/KOR/"):]
        variants = {code: L.unpack(donor.files[f"/script/{folder}/{suffix}"].data)
                    for code, folder in L.LANGUAGES.items()}
        source, translated = L.unpack(file.data), variants[language]
        _, base_count, base_entry = L.bmg_shape(source)
        _, donor_count, donor_entry = L.bmg_shape(translated)
        shared = len(set(variants.values())) == 1
        category = classify(source, translated, shared, suffix.startswith("string/"))
        reachability, evidence = usage(path)
        if evidence is not None:
            category = "documented_unreachable_test_actor"
        rows.append({"path": path, "classification": category,
                     "korean_encoding": source[0x10], "european_encoding": translated[0x10],
                     "korean_messages": base_count, "european_messages": donor_count,
                     "korean_entry_size": base_entry, "european_entry_size": donor_entry,
                     "identical_in_all_five_european_languages": shared,
                     "runtime_usage": reachability, "reachability_evidence": evidence})
    return {"language": language, "base_sha1": L.KR_SHA1, "donor_sha1": L.EU_SHA1,
            "counts": dict(Counter(r["classification"] for r in rows)),
            "warning": "Identical legacy resources suggest leftovers, but do not prove runtime unreachability. "
                       "Equal message counts alone do not prove semantic index compatibility.",
            "files": rows}


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--korean", type=Path, default=L.ROOT / "extract" / "adm-kr.nds")
    ap.add_argument("--european", type=Path, required=True)
    ap.add_argument("--language", choices=L.LANGUAGES, default="es")
    args = ap.parse_args()
    try:
        report = audit(args.korean.read_bytes(), args.european.read_bytes(), args.language)
    except (OSError, ValueError, KeyError) as exc:
        ap.error(str(exc))
    out = L.ROOT / "build" / "localized-clean" / f"audit-{args.language}.json"
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(json.dumps(report["counts"], sort_keys=True))
    print(f"Metadata report (no message text): {out}")


if __name__ == "__main__":
    main()
