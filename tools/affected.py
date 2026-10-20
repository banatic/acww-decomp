"""Which scenes a change can affect (tools/scenes.py --affected).

A scene's Reference run lists the functions the game ran (RUN_FUNCTIONS_SEEN, written by
runtime/native_run.c while it records the crossings, kept in the scene's directory as
functions-seen.txt). A Native or Clean function only runs where the game runs that function, so
a change to it can only change the scenes whose list names it. A change is mapped to functions:

- a source in src/: its own function;
- a header in include/: every source in src/ that includes it;
- a Clean source: the functions it registers (CLEAN_AS); a Clean header: those of every Clean
  source that includes it;
- a scene's recording or expected frames: that scene.

Anything else that runs (config/, runtime/, tools/, libs/) can change every scene, and so do
the Native policy lists: then every scene is chosen. Text that does not run (docs, README) and
the two recordings' files change none. A scene that has no list yet is always chosen.
"""
from __future__ import annotations

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


def functions_of(paths: list[str]) -> tuple[set[tuple[str, int]] | None, set[str]]:
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
    funcs, own = functions_of(changed_paths(base))
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
