"""Which scenes a change can affect (tools/scenes.py --affected).

A scene's Reference run lists the functions the game ran (RUN_FUNCTIONS_SEEN, written by
runtime/native_run.c while it records the crossings, kept in the scene's directory as
functions-seen.txt). A Native or Clean function only runs where the game runs that function, so
a change to it can only change the scenes whose list names it. A change is mapped to functions:

- a source in src/: its own function;
- a header in include/: every source in src/ that includes it;
- a Clean source: the functions it registers (CLEAN_AS); a Clean header: those of every Clean
  source that includes it;
- a scene's recording or expected frames: that scene;
- tools/scenes.py, when only its tables changed (scene() entries, SAVES and its entries, loops
  that only add to them, constants no function reads, and helpers only those use): the scenes
  whose entry or save changed.

Anything else that runs (config/, runtime/, tools/, libs/) can change every scene, and so do
the Native policy lists: then every scene is chosen. Text that does not run (docs, README) and
the two recordings' files change none. A scene that has no list yet is always chosen.
"""
from __future__ import annotations

import ast
import pathlib
import re
import subprocess
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import common as C  # noqa: E402

EVERYTHING = None  # a change no function list can bound
CLEAN_AS = re.compile(r'^CLEAN_AS(?:\((\w+)|_SYMBOL\("([^"]+)"),\s*(\w+)\)', re.M)
QUIET = ("docs/", ".github/", "README", "INSTALL", "CONTRIBUTING", "LICENSE", "AGENTS", "CLAUDE",
         "tests/clean/", "tests/native/known.txt", ".recomp.json", ".gitignore", ".clang-format")


def changed_paths(base: str) -> list[str]:
    """The files that differ from `base`: committed since it, changed in the tree, or new."""
    def git(*args: str) -> list[str]:
        out = subprocess.run(["git", *args], cwd=C.ROOT, capture_output=True, text=True, check=True).stdout
        return [line.strip() for line in out.splitlines() if line.strip()]
    paths = set(git("diff", "--name-only", base))
    paths |= set(git("ls-files", "--others", "--exclude-standard"))
    return sorted(paths)


def _source_function(path: pathlib.Path) -> tuple[str, int] | None:
    src = C.parse_source(path) if path.exists() else None
    return (src.module, src.address & ~1) if src else None


def _clean_functions(path: pathlib.Path) -> set[tuple[str, int]]:
    syms = C.symbol_table(C.modules())
    out = set()
    text = path.read_text(encoding="utf-8", errors="replace") if path.exists() else ""
    for plain, quoted, _ in CLEAN_AS.findall(text):
        for s in syms.by_name.get(plain or quoted, []):
            if s.kind == "function" and s.size:
                out.add((s.module, s.address & ~1))
    return out


def _scene_tables(text: str) -> tuple[str, dict, dict]:
    """tools/scenes.py's code without its tables (as an AST dump), and its SCENES and SAVES."""
    tree = ast.parse(text)
    functions = {n.name: n for n in tree.body if isinstance(n, ast.FunctionDef)}

    def names_in(node: ast.AST) -> set[str]:
        return {n.id for n in ast.walk(node) if isinstance(n, ast.Name)}

    def saves_entry(node: ast.expr) -> bool:
        return isinstance(node, ast.Subscript) and getattr(node.value, "id", None) == "SAVES"

    def table(node: ast.stmt, helpers: set[str], read: set[str]) -> bool:
        """A statement that only adds to SCENES or SAVES, sets a constant no code reads, or
        defines a helper only such statements use."""
        if (isinstance(node, ast.Expr) and isinstance(node.value, ast.Call)
                and getattr(node.value.func, "id", None) == "scene"):
            return True
        if isinstance(node, ast.FunctionDef):
            return node.name in helpers
        if isinstance(node, ast.For):
            return not node.orelse and all(table(n, helpers, read) for n in node.body)
        targets = (node.targets if isinstance(node, ast.Assign) else
                   [node.target] if isinstance(node, ast.AnnAssign) else [])
        if targets and all(saves_entry(t) for t in targets):
            return True
        names = [n.id for n in targets if isinstance(n, ast.Name)]
        return bool(names) and len(names) == len(targets) and all(
            n == "SAVES" or (n.isupper() and n not in read) for n in names)

    # A helper is a function that only the tables (and other helpers) use: what it makes ends up
    # in SCENES or SAVES, which are compared by value below. Start from every function and drop
    # those that the rest of the code names, until nothing changes.
    helpers = set(functions) - {"scene"}
    while True:
        rest = [f for name, f in functions.items() if name not in helpers]
        read = set().union(*map(names_in, rest)) if rest else set()
        others = [n for n in tree.body if not isinstance(n, ast.FunctionDef) and not table(n, helpers, read)]
        used = read.union(*map(names_in, others)) if others else read
        # ... and that the tables do use: a function nothing in the file names may be called
        # from another tool (scenes.derive_save), so it stays code.
        tables = [n for n in tree.body if not isinstance(n, ast.FunctionDef) and n not in others]
        named = set().union(*map(names_in, tables)) if tables else set()
        while True:
            more = named.union(*(names_in(functions[h]) for h in named & helpers))
            if more == named:
                break
            named = more
        keep = (helpers - used) & named
        if keep == helpers:
            break
        helpers = keep

    code = ast.dump(ast.Module(body=[n for n in tree.body if not table(n, helpers, read)], type_ignores=[]))
    space: dict = {"__name__": "scenes_tables", "__file__": str(C.ROOT / "tools" / "scenes.py")}
    exec(compile(text, "scenes.py", "exec"), space)  # noqa: S102 (the repository's own file)
    return code, space["SCENES"], space["SAVES"]


def scene_table_changes(base: str) -> set[str] | None:
    """The scenes whose entry or save differs in tools/scenes.py since `base`, or None when
    more than its tables changed."""
    old = subprocess.run(["git", "show", f"{base}:tools/scenes.py"], cwd=C.ROOT, capture_output=True,
                         text=True)
    if old.returncode != 0:
        return None
    code0, scenes0, saves0 = _scene_tables(old.stdout)
    code1, scenes1, saves1 = _scene_tables((C.ROOT / "tools" / "scenes.py").read_text(encoding="utf-8"))
    if code0 != code1:
        return None
    return {name for name, sc in scenes1.items()
            if scenes0.get(name) != sc or saves0.get(sc["save"]) != saves1.get(sc["save"])}


def functions_of(paths: list[str], base: str = "main") -> tuple[set[tuple[str, int]] | None, set[str]]:
    """(the functions the change touches, or EVERYTHING; the scenes whose own files changed)."""
    funcs: set[tuple[str, int]] = set()
    scenes: set[str] = set()
    headers, clean_headers = set(), set()
    for rel in paths:
        path = C.ROOT / rel
        if rel.startswith(QUIET) or rel.endswith(".md"):
            continue
        if rel.startswith("runtime/recordings/scenes/"):
            scenes.add(pathlib.PurePosixPath(rel).stem)
            continue
        if rel.startswith("runtime/recordings/"):
            continue
        if rel == "tools/scenes.py":
            changed = scene_table_changes(base)
            if changed is None:
                return EVERYTHING, scenes
            scenes |= changed
            continue
        if rel.startswith("src/") and rel.endswith((".c", ".cpp")):
            f = _source_function(path)
            if f is None:
                return EVERYTHING, scenes
            funcs.add(f)
        elif rel.startswith("include/"):
            headers.add(path.resolve())
        elif rel.startswith("clean/") and rel.endswith(".c"):
            funcs |= _clean_functions(path)
        elif rel.startswith("clean/") and rel.endswith(".h"):
            clean_headers.add(path.resolve())
        else:
            return EVERYTHING, scenes  # config, runtime, tools, libs: anything can change
    if headers:
        for src in sorted(C.SRC.rglob("*.c*")):
            if headers & set(C.included_files(src)):
                f = _source_function(src)
                if f is not None:
                    funcs.add(f)
    if clean_headers:
        import run  # noqa: PLC0415 (its header walk, which knows clean/)
        for src in sorted((C.ROOT / "clean").rglob("*.c")):
            if clean_headers & {p.resolve() for p in run.clean_headers(src)}:
                funcs |= _clean_functions(src)
    return funcs, scenes


def seen_functions(listing: pathlib.Path) -> set[tuple[str, int]] | None:
    """The functions a scene's Reference run ran (functions-seen.txt), or None without one."""
    if not listing.exists():
        return None
    out = set()
    for line in listing.read_text().splitlines():
        parts = line.split()
        if len(parts) >= 2:
            out.add((parts[0], int(parts[1], 16)))
    return out


def select(names: list[str], base: str, scene_dir: pathlib.Path) -> list[str]:
    """The scenes of `names` a change since `base` can affect, saying why for each."""
    funcs, own = functions_of(changed_paths(base), base)
    if funcs is EVERYTHING:
        print(f"affected: every scene (a change since {base} outside src/, include/ and clean/)")
        return names
    print(f"affected: {len(funcs)} functions changed since {base}")
    chosen = []
    for name in names:
        seen = seen_functions(scene_dir / name / "functions-seen.txt")
        if name in own:
            why = "its recording changed"
        elif seen is None:
            why = "no list of the functions it runs yet"
        else:
            hit = funcs & seen
            why = f"runs {len(hit)} of them" if hit else ""
        if why:
            chosen.append(name)
            print(f"  {name}: {why}")
    print(f"affected: {len(chosen)} of {len(names)} scenes")
    return chosen
