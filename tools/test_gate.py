"""tools/gate.py's choices on made-up changes: which of the two passes a change to functions
needs from the parts of the PC code that are the base's (passes), and the steps a change gets
(chosen), by kind, with scenes and driven checks of its own."""
from __future__ import annotations

import os
import pathlib
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import affected  # noqa: E402
import gate  # noqa: E402

ALL = set(gate.PARTS)
F, G = ("main", 0x02000100), ("ov004", 0x02200000)
CLEAN, NATIVE = gate.step("diffcheck", []), gate.step("diffcheck-native", [])
UNITS = [name for name, _, _ in gate.unit_steps()]
PLAY = ["play-build"] if os.name == "nt" else []

# (what, the parts that are the base's, the functions touched through src/, those whose Native
# code a Clean run can run) -> (with every Clean function, with Native alone)
PASSES = [
    ("no values kept for the base", None, {F}, set(), (True, True)),
    ("Clean code alone", ALL - {"clean_objects"}, set(), set(), (True, False)),
    ("a Clean function registered", ALL - {"clean_objects", "clean_tables"}, set(), set(), (True, False)),
    ("a source of src/ whose function has a Clean version", ALL - {"native_objects"}, {F}, {G}, (False, True)),
    ("a source of src/ whose function runs Native in a Clean run", ALL - {"native_objects"}, {F, G}, {G}, (True, True)),
    ("Native objects that differ with no source changed", ALL - {"native_objects"}, set(), set(), (True, True)),
    ("a signature (the Native tables)", ALL - {"native_objects", "native_tables"}, {F}, set(), (True, True)),
    ("the Native tables alone", ALL - {"native_tables"}, set(), set(), (True, True)),
    ("a header both use", ALL - {"native_objects", "clean_objects"}, {F}, set(), (True, True)),
    ("the policy with Clean alone", ALL - {"clean_tables"}, set(), set(), (True, False)),
    ("nothing (a comment)", ALL, {F}, set(), (False, False)),
]


def steps(phases: list) -> list[list[list[str]]]:
    return [[[name for name, _, _ in chain] for chain in phase] for phase in phases]


def names_of(phases: list, name: str) -> list[str] | None:
    """The scenes or checks a step runs (the words after its options), or None without the step."""
    for phase in phases:
        for chain in phase:
            for step_name, cmd, _ in chain:
                if step_name == name:
                    return [w for w in cmd[2:] if not w.startswith("-") and w not in (gate.JOBS, gate.VERIFY, "none",
                                                                                      "clean", "native")]
    return None


def check_chosen() -> list[str]:
    bad = []
    Change = affected.Change
    title_native, title_clean = ["title-native", "new-game-native"], ["title-clean", "new-game-clean"]
    both_scenes = [["scenes-clean"], ["scenes-none"]]
    for what, change, names, checks, own, own_checks, need, want in (
            ("Clean code", Change(funcs={F}), ["a"], ["x"], set(), set(), (True, True),
             [[["diffcheck"], title_native, title_clean], both_scenes, [["driven"]]]),
            ("Clean code, the Native side the base's", Change(funcs={F}), ["a"], ["x"], set(), set(), (True, False),
             [[["diffcheck"], title_clean], [["scenes-clean"]], [["driven-clean"]]]),
            ("src/, the Clean side the base's", Change(funcs={F}, native={F}, matching=True), ["a"], ["x"], set(), set(),
             (False, True), [[["diffcheck-native"], title_native], [["scenes-none"]], [["driven-none"]]]),
            ("src/ and Clean code", Change(funcs={F, G}, native={F}), ["a"], [], set(), set(), (True, True),
             [[["diffcheck", "diffcheck-native"], title_native, title_clean], both_scenes]),
            ("a comment, and a scene's recording", Change(funcs={F}, scenes={"a"}), ["a", "b"], ["x"], {"a"}, set(),
             (False, False), [both_scenes]),
            ("a scene's recording", Change(scenes={"a"}), ["a"], [], {"a"}, set(), (True, True), [both_scenes]),
            ("a driven check's file", Change(driven={"x"}), [], ["x"], set(), {"x"}, (True, True), [[["driven"]]]),
            ("the wireless manager's source", Change(features={"RUN_WIRELESS"}, tools=True), ["w"], ["x"], {"w"}, {"x"},
             (True, True), [[UNITS], both_scenes, [["driven"]]]),
            ("the front end", Change(programs={"play"}, tools=True), [], [], set(), set(), (True, True),
             [[*([PLAY] if PLAY else []), UNITS]]),
            ("the front end and Clean code", Change(funcs={F}, programs={"play"}, tools=True), [], [], set(), set(),
             (True, True), [[["diffcheck"], title_native, [*title_clean, *PLAY], UNITS]]),
            ("the function-level check's program", Change(programs={"diffcheck"}, tools=True), [], [], set(), set(),
             (True, True), [[["diffcheck", "diffcheck-native"], UNITS]]),
            ("a tool no run is made of", Change(tools=True), [], [], set(), set(), (True, True), [[UNITS]]),
            ("the title's recording", Change(recordings=True), [], [], set(), set(), (True, True),
             [[title_native, title_clean]]),
            ("text that does not run", Change(), [], [], set(), set(), (True, True), [])):
        got = steps(gate.chosen(change, names, checks, own, own_checks, need, CLEAN, NATIVE))
        if got != want:
            bad.append(f"{what}: {got}, not {want}")
    # scenes of the change's own run both ways; those the functions choose, the way the functions need
    phases = gate.chosen(affected.Change(funcs={F}, scenes={"a"}, driven={"x"}), ["a", "b"], ["x", "y"], {"a"}, {"x"},
                         (True, False), CLEAN, NATIVE)
    got = [names_of(phases, n) for n in ("scenes-clean", "scenes-none", "driven-clean", "driven-none")]
    if got != [["a", "b"], ["a"], ["x", "y"], ["x"]]:
        bad.append(f"own scenes and checks beside the functions': {got}")
    return bad


def main() -> int:
    bad = check_chosen()
    for what, same, native, in_clean, want in PASSES:
        if gate.passes(same, native, in_clean) != want:
            bad.append(f"{what}: passes {gate.passes(same, native, in_clean)}, not {want}")
    if steps([gate.scene_chains([], [])]) != [[["scenes-clean"], ["scenes-none"]]] or gate.scene_chains(None, None):
        bad.append("every scene, or none")
    if steps([gate.driven_chains([], [])]) != [[["driven"]]] or gate.driven_chains(None, None):
        bad.append("every driven check, or none")
    for line in bad:
        print(f"FAIL: {line}")
    print("the gate's choices: " + ("FAIL" if bad else "ok"))
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
