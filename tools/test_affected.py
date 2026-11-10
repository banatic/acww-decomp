"""tools/affected.py's reading of tools/scenes.py on made-up files: which edits are tables only
(the gate runs just the scenes they change) and which are code (the gate runs every check); and
which changed paths a change that only renames may have."""
from __future__ import annotations

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


def main() -> int:
    bad = 0
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
    print(f"{len(CASES) + len(RENAMES) - bad} of {len(CASES) + len(RENAMES)} changes read right")
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
