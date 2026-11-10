"""What a change is, and which scenes and driven checks it can affect (tools/gate.py,
tools/scenes.py --affected, tools/driven.py --affected).

A scene's Reference run lists the functions the game ran (RUN_FUNCTIONS_SEEN, written by
runtime/native_run.c while it records the crossings, kept in the scene's directory as
functions-seen.txt; a driven check's list also has the functions its calls entered). A Native or
Clean function only runs where the game runs that function, so a change to it can only change
the scenes whose list names it. A change is mapped to functions (describe):

- a source in src/: the functions it defines (a unit defines several);
- a header in include/: those of every source in src/ that includes it, and of every Clean
  source and check that does;
- a Clean source: the functions it registers (CLEAN_AS); a Clean header: those of every Clean
  source and check that includes it;
- a check in tests/clean/ (linked into every run with Clean code): the functions its checks
  are for;
- a source that is gone: the functions it had in the base.

Other changes are told apart by what they can reach:

- a scene's recording or expected frames: that scene; a driven check's file: that check;
- tools/scenes.py, when only its tables changed (scene() entries, SAVES and its entries, loops
  that only add to them, constants no function reads, and helpers only those use): the scenes
  whose entry or save changed;
- runtime/wm.c, wifi.c or sequencer.c (the file, not its header): the scenes and driven checks
  that turn its feature on, as the run's code enters it nowhere else (tools/run.py,
  FEATURE_SOURCES; tools/test_run_reference.py checks that on every gate that takes this way);
- a source of another program than the run's (runtime/play.c, the front end; diffcheck.c,
  nativecheck.c and loader.c, the function-level checks'): that program's own check;
- a tool no run is made of (one that tools/native.py, run.py, scenes.py, driven.py and
  diffcheck.py do not import, directly or through another): the lint and the tools' tests.

Anything else that runs (config/, the rest of runtime/ and tools/, libs/) can change every
scene, and so do the Native policy lists: then every check is chosen. Text that does not run
(docs, README) changes none. A scene or check that has no list yet is always chosen.
"""
from __future__ import annotations

import ast
import dataclasses
import functools
import pathlib
import re
import subprocess
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import common as C  # noqa: E402

EVERYTHING = None  # a change no function list can bound
CLEAN_AS = re.compile(r'^CLEAN_AS(?:\((\w+)|_SYMBOL\("([^"]+)"),\s*(\w+)\)', re.M)
QUIET = ("docs/", ".github/", "README", "INSTALL", "CONTRIBUTING", "LICENSE", "AGENTS", "CLAUDE",
         "tests/native/known.txt", ".recomp.json", ".gitignore", ".clang-format")
# the tools every run of the gate is made of; with what they import, a change to one can change
# every run (run_tools)
RUN_ROOTS = ("native.py", "run.py", "scenes.py", "driven.py", "diffcheck.py")
# runtime sources of other programs than the run's: the program whose check a change to one needs
OTHER_PROGRAMS = {"play.c": "play", "diffcheck.c": "diffcheck", "nativecheck.c": "diffcheck", "loader.c": "diffcheck"}
# the files of the two recordings every gate of a source change plays (tools/gate.py, RECORDINGS)
RECORDINGS = ("title-start.txt", "title-start.sha1", "new-game.txt", "new-game.sha1")


def merge_base(base: str) -> str:
    """The commit a change since `base` started from: where this tree's history left `base`'s.
    `base` may have moved on since (main, with other branches merged): what it gained is not this
    tree's change, and comparing with its tip would count it as one."""
    for args in (["merge-base", base, "HEAD"], ["rev-parse", "--verify", f"{base}^{{commit}}"]):
        out = subprocess.run(["git", *args], cwd=C.ROOT, capture_output=True, text=True)
        if out.returncode == 0 and out.stdout.strip():
            return out.stdout.strip()
    raise SystemExit(f"affected: {base} names no commit")


def quiet(rel: str) -> bool:
    """A path whose change no check can see (text that does not run)."""
    return rel.startswith(QUIET) or rel.endswith(".md")


RENAMED = re.compile(r"(?:src|include|clean|tests/clean)/.+|config/[^/]+/arm9/(?:.+/)?symbols\.txt"
                     r"|runtime/native-reference\.txt")


def renames_only(paths: list[str]) -> bool:
    """Whether a change to `paths` can be one that only renames, as far as its paths say: sources,
    headers, Clean code and its checks, the symbol tables, and the list of functions kept
    Reference (by name: tools/run.py reads it into the policy), whose whole effect on a run is in
    the PC objects and tables tools/fingerprint.py compares (and text that does not run). The
    gate then compares those with the base's; anything else changed (the runtime, a tool, a
    recording, another file of config/) runs the checks its kind needs."""
    loud = [rel for rel in paths if not quiet(rel)]
    return bool(loud) and all(RENAMED.fullmatch(rel) for rel in loud)


def changed_paths(base: str) -> list[str]:
    """The files that differ from `base`: committed since it, changed in the tree, or new."""
    def git(*args: str) -> list[str]:
        out = subprocess.run(["git", *args], cwd=C.ROOT, capture_output=True, text=True, check=True).stdout
        return [line.strip() for line in out.splitlines() if line.strip()]
    paths = set(git("diff", "--name-only", base))
    paths |= set(git("ls-files", "--others", "--exclude-standard"))
    return sorted(paths)


def _source_functions(path: pathlib.Path) -> set[tuple[str, int]] | None:
    """The functions a source defines (a unit defines several), or None for no source."""
    srcs = C.parse_sources(path) if path.exists() else []
    return {(src.module, src.address & ~1) for src in srcs} or None


def _removed_functions(rel: str, base: str) -> set[tuple[str, int]] | None:
    """The functions a source that is gone from the tree defined in `base` (one regrouped into a
    unit, or a unit taken apart), or None when `base` has no such source."""
    old = subprocess.run(["git", "show", f"{base}:{rel}"], cwd=C.ROOT, capture_output=True)
    if old.returncode != 0:
        return None
    m = C.HEADER.match(old.stdout.decode("utf-8", "replace"))
    u = C.UNIT_HEADER.match(old.stdout.decode("utf-8", "replace"))
    if m:
        return {(m["module"], int(m["addr"], 16))}
    if u:
        return {(u["module"], int(f["addr"], 16)) for f in C.UNIT_FUNCTION.finditer(u["functions"])}
    return None


def _texts(rel: str, base: str) -> list[str]:
    """A file's text in the tree and in `base` (what it registered there and no longer does has
    changed too), where each has it."""
    path = C.ROOT / rel
    out = [path.read_text(encoding="utf-8", errors="replace")] if path.exists() else []
    old = subprocess.run(["git", "show", f"{base}:{rel}"], cwd=C.ROOT, capture_output=True)
    return out + ([old.stdout.decode("utf-8", "replace")] if old.returncode == 0 else [])


def _clean_functions(text: str) -> set[tuple[str, int]]:
    """The functions a Clean source registers (CLEAN_AS)."""
    syms = C.symbol_table(C.modules())
    out = set()
    for plain, quoted, _ in CLEAN_AS.findall(text):
        for s in syms.by_name.get(plain or quoted, []):
            if s.kind == "function" and s.size:
                out.add((s.module, s.address & ~1))
    return out


def _check_functions(text: str) -> set[tuple[str, int]]:
    """The functions the checks of a file of tests/clean/ are for."""
    import run  # noqa: PLC0415 (its reading of the checks)
    return {(module, address & ~1) for _, module, address, _ in run.checks_in(text)}


def imports_of(source: str) -> set[str]:
    """The modules a Python source imports, anywhere in it (a function's own imports too)."""
    out = set()
    for node in ast.walk(ast.parse(source)):
        if isinstance(node, ast.Import):
            out |= {alias.name.split(".")[0] for alias in node.names}
        elif isinstance(node, ast.ImportFrom) and node.module and not node.level:
            out.add(node.module.split(".")[0])
    return out


def closure(sources: dict[str, str], roots: tuple[str, ...]) -> frozenset[str]:
    """`roots` and every file of `sources` (name -> text) they import, directly or not."""
    seen: set[str] = set()
    todo = [r for r in roots if r in sources]
    while todo:
        name = todo.pop()
        if name not in seen:
            seen.add(name)
            todo += [f"{m}.py" for m in imports_of(sources[name]) if f"{m}.py" in sources]
    return frozenset(seen)


@functools.cache
def run_tools() -> frozenset[str]:
    """The tools the gate's runs are made of: RUN_ROOTS and what they import."""
    sources = {p.name: p.read_text(encoding="utf-8") for p in (C.ROOT / "tools").glob("*.py")}
    return closure(sources, RUN_ROOTS)


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


@dataclasses.dataclass
class Change:
    """What a change is, for choosing its checks (describe)."""
    everything: str | None = None  # the path no list bounds (every check runs), or None
    # the functions it touches, and those of them it touches through src/ or include/ (their
    # Native code; the others only through Clean code)
    funcs: set[tuple[str, int]] = dataclasses.field(default_factory=set)
    native: set[tuple[str, int]] = dataclasses.field(default_factory=set)
    scenes: set[str] = dataclasses.field(default_factory=set)    # the scenes whose own files changed
    driven: set[str] = dataclasses.field(default_factory=set)    # the driven checks whose own files changed
    features: set[str] = dataclasses.field(default_factory=set)  # the RUN_ variables of the gated sources changed
    programs: set[str] = dataclasses.field(default_factory=set)  # "play", "diffcheck": another program's source
    recordings: bool = False  # a file of the two recordings changed
    matching: bool = False    # src/, include/ or config/ changed: the matching checks (verify, link)
    tools: bool = False       # a tool, a test or a source no run is made of changed: the tools' tests


def describe(paths: list[str], base: str = "main", features: dict[str, str] | None = None,
             tools: frozenset[str] | None = None) -> Change:
    """What the change of `paths` since `base` is. `features` (runtime source -> RUN_ variable,
    default tools/run.py's FEATURE_SOURCES) and `tools` (default run_tools) are given by tests."""
    change = Change()
    headers, clean_headers = set(), set()
    rec = C.versions.rel(C.RECORDINGS)

    def everything(rel: str) -> None:
        change.everything = change.everything or rel
    for rel in paths:
        path = C.ROOT / rel
        name = pathlib.PurePosixPath(rel).name
        change.matching = change.matching or rel.startswith(("src/", "include/", "config/"))
        if quiet(rel):
            continue
        if rel.startswith(f"{rec}/scenes/"):
            change.scenes.add(pathlib.PurePosixPath(rel).stem)
        elif rel.startswith(f"{rec}/driven/"):
            change.driven.add(pathlib.PurePosixPath(rel).stem)
        elif rel.startswith("runtime/recordings/"):
            change.recordings = change.recordings or (rel == f"{rec}/{name}" and name in RECORDINGS)
        elif rel == "tools/scenes.py":
            changed = scene_table_changes(base)
            if changed is None:
                everything(rel)
            else:
                change.scenes |= changed
        elif rel.startswith("src/") and rel.endswith((".c", ".cpp")):
            f = _source_functions(path)
            if f is None:
                # a source removed: the functions it had, if a source of the base defined them
                f = _removed_functions(rel, base)
            if f is None:
                everything(rel)
            else:
                change.funcs |= f
                change.native |= f
        elif rel.startswith("include/"):
            headers.add(path.resolve())
        elif rel.startswith("clean/") and rel.endswith(".c"):
            texts = _texts(rel, base)
            if not texts:
                everything(rel)
            for text in texts:
                change.funcs |= _clean_functions(text)
        elif rel.startswith("clean/") and rel.endswith(".h"):
            clean_headers.add(path.resolve())
        elif rel.startswith("tests/clean/") and rel.endswith(".c"):
            texts = _texts(rel, base)
            if not texts:
                everything(rel)
            for text in texts:
                change.funcs |= _check_functions(text)
        elif rel.startswith("tests/clean/") and rel.endswith(".h"):
            clean_headers.add(path.resolve())
        elif rel.startswith("runtime/") and rel.count("/") == 1 and name in OTHER_PROGRAMS:
            change.programs.add(OTHER_PROGRAMS[name])
            change.tools = True
        elif rel.startswith("runtime/") and rel.count("/") == 1 and name in _features(features):
            change.features.add(_features(features)[name])
            change.tools = True  # (tools/test_run_reference.py: the file is entered only under its variable)
        elif rel.startswith("tools/") and rel.count("/") == 1 and name.endswith(".py"):
            if name in (run_tools() if tools is None else tools):
                everything(rel)
            change.tools = True
            change.matching = change.matching or name in ("verify.py", "link.py")
        else:
            everything(rel)  # config, the rest of runtime and tools, libs: anything can change
    if change.everything:
        return change
    if headers:
        for src in sorted(C.SRC.rglob("*.c*")):
            if headers & set(C.included_files(src)):
                f = _source_functions(src) or set()
                change.funcs |= f
                change.native |= f
    if headers or clean_headers:
        import run  # noqa: PLC0415 (its header walk, which knows clean/ and include/)
        for top, functions in ((C.ROOT / "clean", _clean_functions), (C.ROOT / "tests" / "clean", _check_functions)):
            for src in sorted(top.rglob("*.c")):
                if (headers | clean_headers) & {p.resolve() for p in run.clean_headers(src)}:
                    change.funcs |= functions(src.read_text(encoding="utf-8", errors="replace"))
    return change


def _features(given: dict[str, str] | None) -> dict[str, str]:
    if given is not None:
        return given
    import run  # noqa: PLC0415
    return run.FEATURE_SOURCES


def functions_of(paths: list[str], base: str = "main") -> tuple[set[tuple[str, int]] | None, set[str]]:
    """(the functions the change touches, or EVERYTHING; the scenes whose own files changed)."""
    change = describe(paths, base)
    return (EVERYTHING if change.everything else change.funcs), change.scenes


def scene_features(sc: dict) -> set[str]:
    """The RUN_ variables a scene's runs set (tools/scenes.py and tools/run.py: a scene of two
    consoles has its wireless on)."""
    out = set()
    if sc.get("wireless") or sc.get("wifi") or sc.get("peers"):
        out.add("RUN_WIRELESS")
    if sc.get("sequencer"):
        out.add("RUN_SEQUENCER")
    return out


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


def choose(names: list[str], funcs: set[tuple[str, int]], own: set[str], seen, what: str = "scenes") -> list[str]:
    """The scenes (or driven checks) of `names` that a change to `funcs` can affect, or whose own
    files changed (`own`), saying why for each. `seen(name)`: the functions its last run ran, or
    None without a list."""
    chosen = []
    for name in names:
        ran = seen(name)
        if name in own:
            why = "its own files changed, or a runtime source its runs enter"
        elif not funcs:
            why = ""
        elif ran is None:
            why = "no list of the functions it runs yet"
        else:
            hit = funcs & ran
            why = f"runs {len(hit)} of them" if hit else ""
        if why:
            chosen.append(name)
            print(f"  {name}: {why}")
    print(f"affected: {len(chosen)} of {len(names)} {what}")
    return chosen


def select(names: list[str], base: str, scene_dir: pathlib.Path, change: Change | None = None) -> list[str]:
    """The scenes of `names` a change since `base` can affect, saying why for each."""
    change = change or describe(changed_paths(base), base)
    if change.everything:
        print(f"affected: every scene ({change.everything} changed since {base})")
        return names
    print(f"affected: {len(change.funcs)} functions changed since {base}")
    return choose(names, change.funcs, own_scenes(names, change),
                  lambda n: seen_functions(scene_dir / n / "functions-seen.txt"))


def own_scenes(names: list[str], change: Change) -> set[str]:
    """The scenes of `names` whose own files changed, or that turn on a feature whose runtime
    source changed: whatever the functions do, these run."""
    import scenes  # noqa: PLC0415 (it imports this module)
    return (change.scenes & set(names)) | {n for n in names if change.features & scene_features(scenes.SCENES.get(n, {}))}


def own_driven(names: list[str], change: Change) -> set[str]:
    """As own_scenes, for the driven checks (a check's features are its scene's)."""
    own = change.driven & set(names)
    if change.features:
        import driven  # noqa: PLC0415
        import scenes  # noqa: PLC0415
        own |= {n for n in names if change.features & scene_features(scenes.SCENES.get(driven.read_check(n)["scene"], {}))}
    return own


def select_driven(names: list[str], base: str, change: Change | None = None) -> list[str]:
    """The driven checks of `names` a change since `base` can affect: as select, by the list each
    check's last run left (tools/driven.py, seen_listing)."""
    import driven  # noqa: PLC0415
    change = change or describe(changed_paths(base), base)
    if change.everything:
        print(f"affected: every driven check ({change.everything} changed since {base})")
        return names
    return choose(names, change.funcs, own_driven(names, change), lambda n: seen_functions(driven.seen_listing(n)),
                  "driven checks")
