"""tools/affected.py's reading of tools/scenes.py on made-up files: which edits are tables only
(the gate runs just the scenes they change) and which are code (the gate runs every check);
which changed paths a change that only renames may have; what a change to paths outside the
sources is (describe: the paths here need no symbol table); which tools the runs are made of;
and which scenes a set of changed functions chooses."""
from __future__ import annotations

import contextlib
import io
import pathlib
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import affected  # noqa: E402

BASE = '''
SCENES = {}
SAVES = {"seed": []}
MONEY = 0x10


def scene(name, save):
    SCENES[name] = {"save": save}


def derive_save(name):
    return [e for e in SAVES[name]]


scene("a", "seed")
'''

CASES = [
    ("a scene added", BASE + 'scene("b", "seed")\n', {"b"}),
    ("a save entry", BASE + 'SAVES["rich"] = [(MONEY, "<I", 9)]\nscene("b", "rich")\n', {"b"}),
    ("a loop of saves", BASE + 'for n in range(2):\n    SAVES[f"s{n}"] = [(MONEY, "<I", n)]\n'
     'scene("b", "s1")\n', {"b"}),
    ("a helper the saves use", BASE + 'def rich(n):\n    return [(MONEY, "<I", n)]\n\n\n'
     'SAVES["rich"] = rich(9)\nscene("b", "rich")\n', {"b"}),
    ("a save changed", BASE.replace('"seed": []', '"seed": [(1, "<B", 2)]'), {"a"}),
    ("code changed", BASE.replace("return [e for e", "return [e for e in [] if e] or [e for e"), None),
    ("a helper the code uses", BASE.replace("return [e for e in SAVES[name]]", "return pick(name)")
     + 'def pick(name):\n    return SAVES[name]\n', None),
    ("a constant the code reads", BASE.replace("return [e for e in SAVES[name]]", "return [MONEY]")
     .replace("MONEY = 0x10", "MONEY = 0x20"), None),
]


def changes(old: str, new: str) -> set[str] | None:
    code0, scenes0, saves0 = affected._scene_tables(old)
    code1, scenes1, saves1 = affected._scene_tables(new)
    if code0 != code1:
        return None
    return {name for name, sc in scenes1.items()
            if scenes0.get(name) != sc or saves0.get(sc["save"]) != saves1.get(sc["save"])}


RENAMES = [
    (["clean/main/calendar.c", "clean/main/calendar.h", "tests/clean/main/calendar.c"], True),
    (["src/main/func_02000100.c", "include/types.h", "config/adm-kr/arm9/symbols.txt",
      "config/adm-kr/arm9/overlays/ov004/symbols.txt", "docs/naming.md"], True),
    (["docs/naming.md", "README.md"], False),  # nothing that runs: no code to compare
    ([], False),
    (["clean/main/calendar.c", "runtime/run.c"], False),
    (["clean/main/calendar.c", "tools/run.py"], False),
    (["config/adm-kr/arm9/relocs.txt"], False),
    (["config/adm-kr/arm9/symbols.txt", "runtime/native-reference.txt"], False),
    (["clean/main/calendar.c", "runtime/recordings/scenes/fish-cast.txt"], False),
    (["sources/clean/main/calendar.c"], False),
]


REC = affected.C.versions.rel(affected.C.RECORDINGS)
FEATURES = {"wm.c": "RUN_WIRELESS", "sequencer.c": "RUN_SEQUENCER"}
TOOLS = frozenset({"run.py", "common.py", "native.py"})
# paths -> the fields of the Change that are not empty
DESCRIBED = [
    (["docs/runtime.md", "README.md", ".github/workflows/build.yml"], {}),
    (["runtime/wm.c"], {"features": {"RUN_WIRELESS"}, "tools": True}),
    (["runtime/wm.c", "runtime/sequencer.c"], {"features": {"RUN_WIRELESS", "RUN_SEQUENCER"}, "tools": True}),
    (["runtime/wm.h"], {"everything": "runtime/wm.h"}),  # a header: other sources include it
    (["runtime/sub/wm.c"], {"everything": "runtime/sub/wm.c"}),
    (["runtime/arm.c"], {"everything": "runtime/arm.c"}),
    (["runtime/native-reference.txt"], {"everything": "runtime/native-reference.txt"}),
    (["runtime/play.c"], {"programs": {"play"}, "tools": True}),
    (["runtime/diffcheck.c", "runtime/loader.c"], {"programs": {"diffcheck"}, "tools": True}),
    (["tools/report.py", "tools/test_units.py"], {"tools": True}),
    (["tools/run.py"], {"everything": "tools/run.py", "tools": True}),
    (["tools/verify.py"], {"tools": True, "matching": True}),
    (["tools/mwccarm/license.dat"], {"everything": "tools/mwccarm/license.dat"}),
    ([f"{REC}/scenes/fish-cast.txt", f"{REC}/scenes/fish-cast.sha1"], {"scenes": {"fish-cast"}}),
    ([f"{REC}/driven/aquarium-base.txt"], {"driven": {"aquarium-base"}}),
    ([f"{REC}/title-start.sha1"], {"recordings": True}),
    ([f"{REC}/other/title-start.sha1"], {}),  # another version's
    (["config/adm-kr/arm9/symbols.txt"], {"everything": "config/adm-kr/arm9/symbols.txt", "matching": True}),
    (["libs/NitroSDK/main/os.c"], {"everything": "libs/NitroSDK/main/os.c"}),
    (["runtime/wm.c", "tools/run.py"], {"everything": "tools/run.py", "features": {"RUN_WIRELESS"}, "tools": True}),
]


def check_described() -> list[str]:
    bad = []
    empty = affected.Change()
    for paths, want in DESCRIBED:
        got = affected.describe(paths, "HEAD", FEATURES, TOOLS)
        fields = {f.name: getattr(got, f.name) for f in affected.dataclasses.fields(got)
                  if getattr(got, f.name) != getattr(empty, f.name)}
        if fields != want:
            bad.append(f"describe({paths}): {fields}, not {want}")
    return bad


def check_tools() -> list[str]:
    """The tools a run is made of: what the roots import, a function's own imports too."""
    sources = {"run.py": "import os\nimport common as C\nimport native\n", "common.py": "import versions\n",
               "versions.py": "", "native.py": "def main():\n    import objrewrite  # noqa\n", "objrewrite.py": "",
               "report.py": "import common\n", "gate.py": "import affected\nfrom run import build\n", "affected.py": ""}
    bad = []
    got = affected.closure(sources, ("run.py", "scenes.py"))
    if got != {"run.py", "common.py", "versions.py", "native.py", "objrewrite.py"}:
        bad.append(f"the tools of a run: {sorted(got)}")
    if affected.imports_of("from . import x\nfrom .y import z\nimport a.b\nfrom c.d import e\n") != {"a", "c"}:
        bad.append("imports read wrong")
    return bad


def check_chosen() -> list[str]:
    """Scenes by the functions they ran, their own files, and no list yet."""
    ran = {"a": {("main", 0x100), ("main", 0x200)}, "b": {("main", 0x300)}, "c": None, "d": {("ov001", 0x100)}}
    bad = []
    for what, funcs, own, want in (
            ("a changed function", {("main", 0x200)}, set(), ["a", "c"]),
            ("the same address in another module", {("ov001", 0x100)}, set(), ["c", "d"]),
            ("a scene's own files", set(), {"b"}, ["b"]),
            ("a function and a scene's own files", {("main", 0x300)}, {"d"}, ["b", "c", "d"]),
            ("nothing", set(), set(), [])):
        with contextlib.redirect_stdout(io.StringIO()):  # (it says why for each)
            got = affected.choose(list(ran), funcs, own, ran.get)
        if got != want:
            bad.append(f"{what}: chose {got}, not {want}")
    features = affected.scene_features
    if (features({"wireless": True}) != {"RUN_WIRELESS"} or features({"wifi": "1"}) != {"RUN_WIRELESS"}
            or features({"peers": [("a", "b")]}) != {"RUN_WIRELESS"} or features({"sequencer": True}) != {"RUN_SEQUENCER"}
            or features({"wireless": False, "wifi": None, "peers": [], "sequencer": False})):
        bad.append("a scene's features read wrong")
    return bad


def main() -> int:
    bad = 0
    for line in check_described() + check_tools() + check_chosen():
        bad += 1
        print(f"FAIL: {line}")
    for paths, want in RENAMES:
        if affected.renames_only(paths) != want:
            bad += 1
            print(f"FAIL: renames_only({paths}) is not {want}")
    for what, new, want in CASES:
        # the constant case starts from code that reads the constant
        old = BASE.replace("return [e for e in SAVES[name]]", "return [MONEY]") if "constant" in what else BASE
        got = changes(old, new)
        if got != want:
            bad += 1
            print(f"FAIL: {what}: expected {want}, got {got}")
    print("changes read right" if not bad else f"{bad} changes read wrong")
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
