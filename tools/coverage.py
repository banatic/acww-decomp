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
    python tools/coverage.py --record              # runtime/recordings/scenes/clean-entered.txt

--record writes the Clean functions the scenes of tools/scenes.py enter (from their lists, which a
run of every scene leaves) as "module address" lines; CI's progress map counts them as checked in
a run, since a scene is only committed when it agrees both ways. Refresh it after adding scenes.
    python tools/coverage.py --plan docs/scene-plan-groups.txt > docs/scene-plan.md
                                                   # every function no run enters, in the plan's groups

A plan file (docs/scene-plan-groups.txt) is blocks of `key: value` lines separated by blank
lines: `area`, `group`, `scene` (what to play), `reach` (how: save, date, steps), `needs`
(seed, date, unreachable or unknown) and `match` (patterns of `file` or `file:Name`, fnmatch
style, file relative to clean/ without .c). Each function no run enters goes to the first group
with a matching pattern; --plan stops with the functions no group takes, and warns (on stderr)
about each group marked unreachable whose patterns take a function some scene ran (the first
group matching it): such a group claims more than it proves. tools/lint.py fails on such a group
by the committed runtime/recordings/scenes/clean-entered.txt (unreachable_ran below).
"""
from __future__ import annotations

import argparse
import collections
import fnmatch
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


PLAN_NEEDS = ("seed", "date", "unknown", "unreachable")


def read_plan(path: pathlib.Path) -> list[dict]:
    """The groups of a plan file, in order."""
    groups = []
    for block in re.split(r"\n\s*\n", path.read_text(encoding="utf-8")):
        lines = [ln for ln in block.splitlines() if ln.strip() and not ln.startswith("#")]
        if not lines:
            continue
        g: dict = {}
        key = None
        for ln in lines:
            m = re.match(r"(\w+):\s*(.*)", ln)
            if m and m.group(1) in ("area", "group", "scene", "reach", "needs", "match"):
                key = m.group(1)
                g[key] = m.group(2).strip()
            elif key:
                g[key] += " " + ln.strip()
        missing = [k for k in ("area", "group", "scene", "reach", "needs", "match") if k not in g]
        if missing or g["needs"] not in PLAN_NEEDS:
            raise SystemExit(f"{path}: group {g.get('group')}: missing {missing} or bad needs {g.get('needs')}")
        g["patterns"] = g["match"].split()
        groups.append(g)
    return groups


def group_of(groups: list[dict], f: str, name: str) -> dict | None:
    """The first group whose patterns match a Clean function (file f, Clean name)."""
    for g in groups:
        if any(fnmatch.fnmatchcase(f, p) if ":" not in p else fnmatch.fnmatchcase(f"{f}:{name}", p)
               for p in g["patterns"]):
            return g
    return None


def unreachable_ran(syms, plan: pathlib.Path = C.ROOT / "docs" / "scene-plan-groups.txt") -> list[str]:
    """The plan's unreachable groups that take a function a committed scene enters (by
    runtime/recordings/scenes/clean-entered.txt, which needs no scene run), one line a group."""
    entered = set()
    for line in (C.ROOT / "runtime" / "recordings" / "scenes" / "clean-entered.txt").read_text().splitlines():
        parts = line.split()
        if len(parts) == 2 and not line.startswith("#"):
            entered.add((parts[0], int(parts[1], 16)))
    groups = read_plan(plan)
    out = collections.defaultdict(list)
    for k, (f, name) in sorted(clean_functions(syms).items()):
        g = group_of(groups, f, name) if k in entered else None
        if g is not None and g["needs"] == "unreachable":
            out[g["group"]].append(f"{f}:{name}")
    return [f"{plan.relative_to(C.ROOT).as_posix()}: group \"{group}\" is unreachable but takes {len(names)} "
            f"functions a scene enters, e.g. {', '.join(names[:5])}" for group, names in out.items()]


def write_plan(groups: list[dict], clean: dict, state, counts: dict, lists: int) -> None:
    """Every function no run enters, by group, as Markdown on stdout."""
    left = []
    contradicted = collections.defaultdict(list)  # unreachable group -> functions a scene ran
    for g in groups:
        g["functions"] = []
    for k in sorted(clean, key=lambda k: (clean[k][0], k)):
        f, name = clean[k]
        g = group_of(groups, f, name)
        if g is None:
            if state(k) != "run":
                left.append(f"{f}:{name}")
        elif state(k) != "run":
            g["functions"].append((k, state(k)))
        elif g["needs"] == "unreachable":
            contradicted[g["group"]].append(f"{f}:{name}")
    for group, names in contradicted.items():
        print(f"warning: group \"{group}\" is unreachable but takes {len(names)} functions a scene ran, "
              f"e.g. {', '.join(names[:5])}", file=sys.stderr)
    if left:
        raise SystemExit(f"{len(left)} functions no group takes, e.g. " + ", ".join(left[:20]))
    out = []
    total = sum(len(g["functions"]) for g in groups)
    out.append(f"From {lists} scene lists: {len(clean):,} Clean game functions, run {counts['run']:,}, "
               f"function check only {counts['function']:,}, read only {counts['read']:,}; "
               f"the groups below hold {total:,} (function check only + read only).\n")
    by_needs = collections.Counter()
    for g in groups:
        by_needs[g["needs"]] += len(g["functions"])
    out.append("| needs | functions |\n|---|---|")
    for n in PLAN_NEEDS:
        out.append(f"| {n} | {by_needs[n]:,} |")
    out.append(f"| total | {total:,} |\n")
    areas = list(dict.fromkeys(g["area"] for g in groups))
    for area in areas:
        rows = sorted((g for g in groups if g["area"] == area and g["functions"]), key=lambda g: -len(g["functions"]))
        if not rows:
            continue
        n = sum(len(g["functions"]) for g in rows)
        out.append(f"## {area} ({n:,})\n")
        out.append("| group | functions (check only / read only) | Clean files | scene | how to reach it | needs |")
        out.append("|---|---|---|---|---|---|")
        for g in rows:
            files = collections.Counter(clean[k][0] for k, _ in g["functions"])
            fc = sum(1 for _, s in g["functions"] if s == "function")
            listed = ", ".join(f"{f} {c}" for f, c in files.most_common(8))
            if len(files) > 8:
                listed += f", {len(files) - 8} more files ({sum(c for _, c in files.most_common()[8:])})"
            out.append(f"| {g['group']} | {len(g['functions'])} ({fc} / {len(g['functions']) - fc}) | {listed} | "
                       f"{g['scene']} | {g['reach']} | {g['needs']} |")
        out.append("")
    sys.stdout.write("\n".join(out) + "\n")


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--lists", type=pathlib.Path, default=C.BUILD / "scenes")
    ap.add_argument("--file", help="one Clean file (relative to clean/, no .c)")
    ap.add_argument("--top", type=int, default=40)
    ap.add_argument("--json", type=pathlib.Path)
    ap.add_argument("--record", action="store_true",
                    help="write runtime/recordings/scenes/clean-entered.txt (the scenes' Clean functions)")
    ap.add_argument("--plan", type=pathlib.Path, help="a plan file: print every function no run enters by its group")
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

    if args.record:
        import scenes  # noqa: PLC0415
        missing = sorted(set(scenes.SCENES) - set(lists))
        if missing:
            raise SystemExit(f"no list for {', '.join(missing)} (run them with tools/scenes.py first)")
        entered = sorted({k for name in scenes.SCENES for k in lists[name] if k in clean})
        out = scenes.RECORDINGS / "clean-entered.txt"
        out.write_text("# The Clean functions the scenes of tools/scenes.py enter (tools/coverage.py --record)\n"
                       + "".join(f"{m} {a:08x}\n" for m, a in entered), newline="\n")
        print(f"{out}: {len(entered):,} Clean functions from {len(scenes.SCENES)} scenes")
        return

    if args.plan:
        counts = collections.Counter(state(k) for k in clean)
        write_plan(read_plan(args.plan), clean, state, counts, len(lists))
        return

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
