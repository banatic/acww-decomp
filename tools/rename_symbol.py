"""Rename a symbol in the symbol table, every source that uses it, and its file name.

    python tools/rename_symbol.py <module> <address> <old> <new>
    python tools/rename_symbol.py --tsv renames.tsv     # columns: module address old new

Refuses names that are already taken or not at that address. Run tools/verify.py on the
printed paths afterwards.
"""

from __future__ import annotations

import argparse
import pathlib
import re
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import common as C  # noqa: E402


def table_files(module: str) -> list[pathlib.Path]:
    d = C.config_dir(module)
    return [p for p in (d / "symbols.txt", d / "recovered.txt") if p.exists()]


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("args", nargs="*")
    ap.add_argument("--tsv", type=pathlib.Path)
    ap.add_argument("--dry-run", action="store_true")
    a = ap.parse_args()

    rows: list[tuple[str, int, str, str]] = []
    if a.tsv:
        for line in a.tsv.read_text(encoding="utf-8").splitlines()[1:]:
            f = line.split("\t")
            rows.append((f[0], int(f[1], 16), f[2], f[3]))
    elif len(a.args) == 4:
        rows.append((a.args[0], int(a.args[1], 16), a.args[2], a.args[3]))
    else:
        ap.error("give <module> <address> <old> <new>, or --tsv")

    syms = C.SymbolTable(C.modules())
    taken = {name for name in syms.by_name}
    renames: dict[str, str] = {}
    skipped = []
    for mod, addr, old, new in rows:
        if new in taken or new in renames.values():
            skipped.append(f"{old} -> {new}: {new} is already a symbol")
            continue
        if not any(s.name == old for s in syms.by_addr.get((mod, addr), ())):
            skipped.append(f"{old} -> {new}: no {old} at {mod} {addr:#010x}")
            continue
        if old in renames:
            skipped.append(f"{old} -> {new}: {old} is renamed twice")
            continue
        if len(syms.by_name.get(old, ())) > 1:
            skipped.append(f"{old} -> {new}: {old} names more than one symbol")
            continue
        renames[old] = new

    if not renames:
        print("\n".join(skipped) or "nothing to do")
        return
    word = re.compile(r"\b(" + "|".join(map(re.escape, sorted(renames, key=len, reverse=True)))
                      + r")\b")

    touched_cfg = 0
    for mod in {r[0] for r in rows}:
        for p in table_files(mod):
            text = p.read_text(encoding="utf-8")
            new = re.sub(r"(?m)^(\S+)(?=\s+kind:)",
                         lambda m: renames.get(m.group(1), m.group(1)), text)
            if new != text:
                touched_cfg += 1
                if not a.dry_run:
                    p.write_text(new, encoding="utf-8", newline="\n")

    touched: list[pathlib.Path] = []
    for path in C.all_sources():
        text = path.read_text(encoding="utf-8")
        new = word.sub(lambda m: renames[m.group(1)], text)
        dest = path
        if path.stem in renames:
            dest = path.with_name(renames[path.stem] + path.suffix)
            if dest.exists():
                skipped.append(f"{path.name}: {dest.name} already exists, file not renamed")
                dest = path
        if new != text or dest != path:
            touched.append(dest)
            if not a.dry_run:
                dest.write_text(new, encoding="utf-8", newline="\n")
                if dest != path:
                    path.unlink()

    print(f"{len(renames)} symbols renamed in {touched_cfg} table files and "
          f"{len(touched)} sources{' (dry run)' if a.dry_run else ''}")
    for s in skipped:
        print("  skipped:", s)
    out = C.BUILD / "renamed-sources.txt"
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text("\n".join(p.relative_to(C.ROOT).as_posix() for p in touched) + "\n")
    print(f"  touched sources listed in {out.relative_to(C.ROOT)}")


if __name__ == "__main__":
    main()
