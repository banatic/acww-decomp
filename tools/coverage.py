"""Which Clean functions no run enters yet, and where a new scene would reach them.

A scene's Reference run lists the functions the game ran (functions-seen.txt, see
tools/affected.py). This tool takes the union over the scenes and the two recordings, and
reports, for the game's Clean functions:

- how many ran, how many only the function-level check covers (build/adm-kr/clean-checked.json),
  and how many are checked only by reading;
- the Clean files with the most functions no run enters;
- the frontier: functions no run enters whose source is called by a function some scene runs,
  with that caller and the scenes that run it, so a new scene knows where to start.

    python tools/coverage.py                       # the lists in build/adm-kr/scenes/*/
    python tools/coverage.py --lists DIR           # DIR/*.txt or DIR/*/functions-seen.txt
    python tools/coverage.py --file ov003/field_actor   # one Clean file's functions, by state
    python tools/coverage.py --json FILE           # also write the rows as JSON
"""
from __future__ import annotations

import argparse
import collections
import json
import pathlib
import re
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import common as C  # noqa: E402

CLEAN_AS = re.compile(r'^CLEAN_AS(?:\((\w+)|_SYMBOL\("([^"]+)"),\s*(\w+)\)', re.M)
CALL = re.compile(r"\b([A-Za-z_]\w*)\s*\(")

Key = tuple[str, int]


def scene_lists(where: pathlib.Path) -> dict[str, set[Key]]:
    """name -> the functions its run ran."""
    out: dict[str, set[Key]] = {}
    paths = sorted(where.glob("*/functions-seen.txt")) + sorted(where.glob("*.txt"))
    for path in paths:
        name = path.parent.name if path.name == "functions-seen.txt" else path.stem
        seen = set()
        for line in path.read_text().splitlines():
            parts = line.split()
            if len(parts) >= 2:
                seen.add((parts[0], int(parts[1], 16) & ~1))
        out[name] = seen
    return out


def clean_functions(syms) -> dict[Key, tuple[str, str]]:
    """(module, address) -> (Clean file relative to clean/, without .c; Clean name)."""
    out = {}
    root = C.ROOT / "clean"
    for path in sorted(root.rglob("*.c")):
        rel = path.relative_to(root).with_suffix("").as_posix()
        for plain, quoted, name in CLEAN_AS.findall(path.read_text(encoding="utf-8", errors="replace")):
            for s in syms.by_name.get(plain or quoted, []):
                if s.kind == "function" and not C.in_library(s.module, s.address & ~1):
                    out[(s.module, s.address & ~1)] = (rel, name)
    return out


def callers(syms) -> dict[Key, set[Key]]:
    """callee -> its callers, from the names the matching sources call."""
    out: dict[Key, set[Key]] = collections.defaultdict(set)
    for path in sorted(C.SRC.rglob("*.c*")):
        src = C.parse_source(path)
        if src is None:
            continue
        me = (src.module, src.address & ~1)
        text = path.read_text(encoding="utf-8", errors="replace")
        for name in set(CALL.findall(text)):
            for s in syms.by_name.get(name, []):
                if s.kind == "function":
                    callee = (s.module, s.address & ~1)
                    if callee != me:
                        out[callee].add(me)
    return out


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--lists", type=pathlib.Path, default=C.BUILD / "scenes")
    ap.add_argument("--file", help="one Clean file (relative to clean/, no .c)")
    ap.add_argument("--top", type=int, default=40)
    ap.add_argument("--json", type=pathlib.Path)
    args = ap.parse_args()

    syms = C.symbol_table(C.modules())
    clean = clean_functions(syms)
    lists = scene_lists(args.lists)
    if not lists:
        raise SystemExit(f"{args.lists}: no lists (run tools/scenes.py first)")
    ran_by: dict[Key, list[str]] = collections.defaultdict(list)
    for name, seen in lists.items():
        for k in seen:
            ran_by[k].append(name)
    checked = set()
    path = C.BUILD / "clean-checked.json"
    if path.exists():
        checked = {(r["module"], int(r["address"], 16) & ~1) for r in json.loads(path.read_text())}

    def state(k: Key) -> str:
        return "run" if k in ran_by else "function" if k in checked else "read"

    names = {(s.module, s.address & ~1): s.name for s in syms.functions() if s.size} \
        if hasattr(syms, "functions") else {}

    if args.file:
        rows = sorted((k for k, (f, _) in clean.items() if f == args.file), key=lambda k: k[1])
        for k in rows:
            print(f"{state(k):8} {k[0]} {k[1]:08x} {clean[k][1]}  {' '.join(sorted(ran_by.get(k, []))[:6])}")
        return

    total = len(clean)
    count = collections.Counter(state(k) for k in clean)
    print(f"{len(lists)} lists; {total:,} Clean game functions: run {count['run']:,}, "
          f"function check only {count['function']:,}, read only {count['read']:,}")

    per_file = collections.Counter(clean[k][0] for k in clean if state(k) == "read")
    sizes = collections.Counter(f for f, _ in clean.values())
    print(f"\nClean files with the most functions read only (of {len(per_file)} files):")
    for f, n in per_file.most_common(args.top):
        print(f"  {n:5} of {sizes[f]:5}  {f}")

    calls = callers(syms)
    frontier = collections.defaultdict(list)  # file -> (callee, caller)
    for k in clean:
        if state(k) != "read":
            continue
        reached = sorted(c for c in calls.get(k, ()) if c in ran_by)
        if reached:
            frontier[clean[k][0]].append((k, reached[0]))
    n_front = sum(len(v) for v in frontier.values())
    print(f"\nfrontier: {n_front:,} read-only functions are called by a function some run enters "
          f"(the rest are reached only through pointers, or through other unreached code)")
    for f, rows in sorted(frontier.items(), key=lambda kv: -len(kv[1]))[:args.top]:
        k, caller = rows[0]
        scenes = sorted(ran_by[caller])
        print(f"  {len(rows):5}  {f}: e.g. {clean[k][1]} from {names.get(caller, f'{caller[1]:08x}')} "
              f"({', '.join(scenes[:3])}{'...' if len(scenes) > 3 else ''})")

    if args.json:
        rows = [{"module": k[0], "address": f"{k[1]:08x}", "file": clean[k][0], "name": clean[k][1],
                 "state": state(k), "scenes": sorted(ran_by.get(k, []))} for k in sorted(clean)]
        args.json.write_text(json.dumps(rows, indent=1) + "\n", newline="\n")


if __name__ == "__main__":
    main()
