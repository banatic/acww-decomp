"""Every function the Native tables name, by its key (common.function_key).

    python tools/native_tables.py [--check]

The tables (runtime/native-*.json, runtime/native-member-sources.txt and those in
tools/native_*.py) pin a function by its key and the SHA-256 of its own text
(common.function_sha256), so they hold whichever file defines it: a file of one function or a
unit (tools/regroup.py). tools/lint.py checks that each key is still a function of a source;
`--check` also checks each digest against the current text, without the ROM.
"""
from __future__ import annotations

import pathlib
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import common as C  # noqa: E402


def pinned() -> list[tuple[str, str, str | None]]:
    """(table, function key, the digest it pins or None) for every entry of every table."""
    import native_aggregate
    import native_args
    import native_contract
    import native_layout
    import native_pmf
    import native_pmf_boundary
    import native_publish
    import native_stack
    import native_statics
    import native_virtual
    out = []
    out += [("runtime/native-aggregate.json", k, v["function_sha256"]) for k, v in native_aggregate.SPECS.items()]
    out += [("tools/native_aggregate.py", k, v[0]) for k, v in native_aggregate.CALLERS.items()]
    out += [("tools/native_aggregate.py", native_aggregate.SCALAR_CALLER, None)]
    out += [("tools/native_args.py", k, v[0]) for k, v in {**native_args.PASSED, **native_args.EDITS}.items()]
    out += [("tools/native_contract.py", c.source, c.source_sha256) for c in native_contract.CONTRACTS]
    out += [("tools/native_layout.py", k, v[0]) for k, v in native_layout.VERIFIED.items()]
    out += [("tools/native_pmf.py", k, v[0]) for k, v in native_pmf.VERIFIED.items()]
    out += [("runtime/native-member-sources.txt", k, v) for k, v in native_pmf.READ_ONLY.items()]
    out += [("runtime/native-member-boundary.json", k, v["function_sha256"]) for k, v in native_pmf.BOUNDARY.items()]
    out += [("tools/native_pmf_boundary.py", k, None) for k in native_pmf_boundary.REGISTER_CALLS]
    out += [("tools/native_publish.py", k, None) for k in native_publish.paths() if not k.startswith("clean/")]
    out += [("tools/native_stack.py", k, native_stack.SOURCES.get(k)) for k in native_stack.paths()]
    out += [("runtime/native-rom-statics.json", k, v["function_sha256"]) for k, v in native_statics.SPECS.items()]
    out += [("tools/native_virtual.py", k, v[0]) for k, v in native_virtual.VERIFIED.items()]
    return out


def keys() -> list[tuple[str, str]]:
    """(table, function key) for every entry of every table."""
    return [(table, key) for table, key, _ in pinned()]


def main() -> None:
    problems = []
    rows = pinned()
    for table, key, digest in rows:
        src = C.function_source(key)
        if src is None:
            problems.append(f"{table}: {key} is not a function of a source")
        elif digest is not None and C.pinned_sha256(key, src.path.read_text(encoding="utf-8")) != digest:
            problems.append(f"{table}: {key} changed since the audit")
    for p in problems:
        print(p)
    print(f"{len(rows)} entries for {len({k for _, k, _ in rows})} functions, {len(problems)} problems")
    if problems and sys.argv[1:] == ["--check"]:
        raise SystemExit(1)


if __name__ == "__main__":
    main()
