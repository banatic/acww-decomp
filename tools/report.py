"""Write an objdiff-format progress report (build/adm-kr/report.json) for decomp.dev.

    python tools/verify.py && python tools/report.py

Every sized function in config/ counts. A function is "matched" when its source passes
BYTES and "linked" when it also passes LINK (see docs/verification.md). Units are
`game/<module>` and `libs/<module>`; functions without a source are placed by
common.LIBRARY_RANGES. Schema: objdiff-core report.proto, version 2.
"""

from __future__ import annotations

import json
import pathlib
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import common as C  # noqa: E402

REPORT_VERSION = 2
OUT = C.BUILD / "report.json"
CATEGORIES = {"game": "Game", "libs": "Libraries"}


def measures(funcs: list[dict], units: int, complete_units: int) -> dict:
    total = sum(f["size"] for f in funcs)
    matched = sum(f["size"] for f in funcs if f["matched"])
    complete = sum(f["size"] for f in funcs if f["complete"])
    nmatched = sum(1 for f in funcs if f["matched"])

    def pct(a: int, b: int) -> float:
        return 100.0 * a / b if b else 100.0

    return {
        "fuzzy_match_percent": pct(matched, total),
        "total_code": total, "matched_code": matched,
        "matched_code_percent": pct(matched, total),
        "total_data": 0, "matched_data": 0, "matched_data_percent": 100.0,
        "total_functions": len(funcs), "matched_functions": nmatched,
        "matched_functions_percent": pct(nmatched, len(funcs)),
        "complete_code": complete, "complete_code_percent": pct(complete, total),
        "complete_data": 0, "complete_data_percent": 100.0,
        "total_units": units, "complete_units": complete_units,
    }


def functions() -> dict[tuple[str, str], list[dict]]:
    """(category, module) -> its functions, from the symbol table and verify.json."""
    mods = C.modules()
    syms = C.SymbolTable(mods)
    results = {}
    for r in json.loads((C.BUILD / "verify.json").read_text()):
        if "module" in r:
            results[(r["module"], int(r["address"], 16))] = r
    out: dict[tuple[str, str], list[dict]] = {}
    for mod in mods:
        seen = set()
        for s in syms.by_module.get(mod, ()):
            if s.kind != "function" or not s.size or s.address in seen:
                continue
            seen.add(s.address)
            sym = syms.function(mod, s.address)
            r = results.get((mod, s.address))
            if r is not None:
                cat = "libs" if r["file"].startswith("libs/") else "game"
            else:
                cat = "libs" if C.in_library(mod, s.address) else "game"
            status = r["status"] if r else None
            out.setdefault((cat, mod), []).append({
                "name": sym.name, "address": s.address, "size": sym.size,
                "has_source": r is not None, "file": r["file"] if r else None,
                "matched": status in ("ok", "link"), "complete": status == "ok"})
    return out


def main() -> None:
    mods = C.modules()
    groups = functions()
    units, everything = [], []
    per_cat: dict[str, list[dict]] = {k: [] for k in CATEGORIES}
    cat_units = {k: [0, 0] for k in CATEGORIES}
    order = sorted(groups, key=lambda k: (k[0] != "game", k[1].startswith("ov"), k[1]))
    for cat, mod in order:
        funcs = sorted(groups[(cat, mod)], key=lambda f: f["address"])
        done = all(f["complete"] for f in funcs)
        base = mods[mod]["base"]
        size = sum(f["size"] for f in funcs)
        units.append({
            "name": f"{cat}/{mod}",
            "measures": measures(funcs, 1, int(done)),
            "sections": [{"name": ".text", "size": size,
                          "fuzzy_match_percent": 100.0 * sum(f["size"] for f in funcs
                                                             if f["matched"]) / max(1, size)}],
            "functions": [{"name": f["name"], "size": f["size"],
                           "fuzzy_match_percent": 100.0 if f["matched"] else 0.0,
                           "address": f["address"] - base,
                           "metadata": {"virtual_address": f["address"]}} for f in funcs],
            "metadata": {"complete": done, "module_name": mod,
                         "module_id": int(mod[2:]) if mod.startswith("ov") else 0,
                         "source_path": "src/" + mod if cat == "game" else "libs",
                         "progress_categories": [cat]},
        })
        everything += funcs
        per_cat[cat] += funcs
        cat_units[cat][0] += 1
        cat_units[cat][1] += int(done)

    report = {
        "measures": measures(everything, len(units), sum(c[1] for c in cat_units.values())),
        "units": units,
        "version": REPORT_VERSION,
        "categories": [{"id": k, "name": v, "measures": measures(per_cat[k], *cat_units[k])}
                       for k, v in CATEGORIES.items()],
    }
    OUT.write_text(json.dumps(report, indent=1) + "\n")
    m = report["measures"]
    print(f"{OUT.relative_to(C.ROOT)}: {len(units)} units, {m['total_functions']} functions "
          f"({sum(not f['has_source'] for f in everything)} without a source), "
          f"matched {m['matched_code_percent']:.2f}%, linked {m['complete_code_percent']:.2f}%")
    for c in report["categories"]:
        cm = c["measures"]
        print(f"  {c['id']:<5} {cm['total_functions']:>6} functions, {cm['total_code']:>9,} "
              f"bytes, matched {cm['matched_code_percent']:.2f}%, "
              f"linked {cm['complete_code_percent']:.2f}%")


if __name__ == "__main__":
    main()
