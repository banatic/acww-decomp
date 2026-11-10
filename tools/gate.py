"""The checks a change needs before it is committed, chosen from what it changed (tools/affected.py).

    python tools/gate.py               # the checks a change since main needs
    python tools/gate.py BASE          # ... since BASE
    python tools/gate.py --full        # every check
    python tools/gate.py --dry-run     # only say which checks would run
    python tools/gate.py --keep-going  # do not stop at the first failure
    python tools/gate.py --ignore-fingerprint  # choose as if no values were kept for the base (see below)

A change is what differs from the commit this tree left BASE at (their merge base: what BASE
gained since is not this tree's change), committed or not.

A change that only adds or changes scenes (recordings, expected frames, tools/scenes.py's
tables) runs those scenes both ways (all Clean, and Native alone) and the lint. A change to
sources in src/, include/, clean/ or tests/clean/ also runs the function-level checks (the
Clean functions; the Native ones too when src/ or include/ changed) and the two recordings both
ways, and the scenes and driven checks (tools/driven.py) whose last run ran a function it
touches; a change that adds or changes driven checks runs those. A change to runtime/wm.c,
wifi.c or sequencer.c runs the scenes and driven checks that turn that feature on, and the
tools' tests; one to another program's source (runtime/play.c; the function-level checks') runs
that program's check; one to a tool no run is made of runs the tools' tests (tools/affected.py
tells these apart). Anything else (the rest of runtime/ and tools/, config/) runs every check.
A change to src/, include/ or config/ first checks the matching sources as CI does:
tools/verify.py (every function of src/ ok), tools/link.py, and that the link leaves
runtime/native-private.txt as it is. The seed save comes from ACWW_SCENE_SEED, as for
tools/scenes.py. Each step's output goes to build/<version>/gate/<step>.log (build/adm-kr/gate
by default, tools/versions.py); the exit status is 1 when a step failed.

A change that only renames runs almost nothing. After the Native build, the fingerprint step
(tools/fingerprint.py) takes the PC code of this tree, Native and Clean objects and the tables
they are linked with, as four values that do not depend on names. A gate that passes on a tree
with nothing uncommitted keeps them under its commit, in the cache every checkout shares. When
a change touches only sources, headers, Clean code and symbol tables, and all four values are
those kept for the commit it started from, the code every check would run is the code that
passed there: the gate then runs the lint, the matching checks, the tools' tests and the title
recording once, and passes. If any value differs, or none is kept for that commit (run this
tool there once: with nothing changed it is quick), it goes on as for any change.

The same values say which pass a change to functions needs (passes). Clean code alone changed,
and the Native objects and tables are the base's: the scenes, recordings and driven checks run
with every Clean function only. Sources of src/ alone changed, the Clean objects and every
table are the base's, and each function touched has a Clean version (which runs in its place
in a run with Clean code): they run with Native alone only. Scenes and driven checks whose own
files changed run both ways. Without the base's values both passes run. --ignore-fingerprint
chooses as if there were none: no short way for a change of names, and both passes.

The cheap checks come first, and the first failure stops the rest: the lint runs beside the
Native build, then the tools' own tests, the function-level check and the two recordings (each
kind of program in a runtime directory of its own, side by side), and only then the scenes
and the driven checks, which are nearly all of a gate's time. When a step fails, the steps not
yet started are left out, and the scenes and driven checks still waiting in a running step are
too (ACWW_GATE_STOP names a file the gate's steps make at a failure and look for before each
run; tools/common.py, gate_stopped); what is running finishes. --keep-going runs everything.

The two scene passes run at the same time: they build and run in directories of their own
(tools/scenes.py locks its runtime directories, and keeps Native alone's logs apart). A scene
uses about one and a half CPUs; each pass runs three eighths of the CPUs' count of scenes at a
time (6 of 16: on 24 scenes 4 a pass took 908 s, 6 took 731 s, with another tree's gate running;
ACWW_GATE_JOBS sets it).
"""
from __future__ import annotations

import concurrent.futures as cf
import json
import os
import pathlib
import subprocess
import sys
import threading
import time
from collections.abc import Iterator

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import affected  # noqa: E402
import common as C  # noqa: E402

PY = sys.executable
RTC = "2005-11-23 12:00:00"
JOBS = os.environ.get("ACWW_GATE_JOBS") or str(max(1, (os.cpu_count() or 4) * 3 // 8))
VERIFY = os.environ.get("ACWW_GATE_VERIFY") or "2"  # scenes a pass runs its Reference again for
REC = C.versions.rel(C.RECORDINGS)  # runtime/recordings for adm-kr (tools/versions.py)
RECORDINGS = [
    ("title", f"{REC}/title-start", 1300, "100,390,500,700,1000,1299"),
    ("new-game", f"{REC}/new-game", 13760, "1299,2600,7200,9750,12100,13300,13759"),
]
RUNTIME = C.BUILD / ("runtime" if os.name == "nt" else "runtime-linux")  # tools/run.py's OUT
FINGERPRINT = C.BUILD / "gate" / "fingerprint.json"  # this tree's, as the fingerprint step writes it
PARTS = ("native_objects", "native_tables", "clean_objects", "clean_tables")  # tools/fingerprint.py

# A step: its name (and log), its command, and what it adds to the environment.
Step = tuple[str, list[str], dict[str, str]]
Chain = list[Step]    # steps run one after another
Phase = list[Chain]   # chains run side by side


def step(name: str, cmd: list[str], **env: str) -> Step:
    return name, cmd, env


def recording_chains(native: bool = True, clean: bool = True) -> Phase:
    """The two recordings as Native alone and with the Clean functions: a chain for each kind of
    program, in a runtime directory of its own (ACWW_RUNTIME_OUT), so the two run side by side
    and beside the function-level check, which builds in tools/run.py's usual directory."""
    chains: Phase = []
    for kind, wanted, extra in (("native", native, []), ("clean", clean, ["--clean"])):
        if not wanted:
            continue
        chain = []
        for name, rec, frames, ram in RECORDINGS:
            cmd = [PY, "tools/run.py", "0", str(frames), "--input", f"{rec}.txt", "--rtc", RTC, "--native=all",
                   "--ram-hash", ram, "--expect", f"{rec}.sha1", *extra]
            chain.append(step(f"{name}-{kind}", cmd, ACWW_RUNTIME_OUT=str(RUNTIME / f"gate-{kind}")))
        chains.append(chain)
    return chains


def scene_chains(clean: list[str] | None, native: list[str] | None) -> Phase:
    """The two passes, each a chain of its own (they run side by side): the scenes to run with
    every Clean function, and with Native alone. An empty list is every scene; None, or a list
    that had names and has none left, is no pass."""
    # a few of each pass's cached Reference runs are made again: a key that leaves out something
    # a run depends on shows as a failed step (tools/run.py, ACWW_REFERENCE_VERIFY)
    verify = ["--verify-cache", VERIFY]
    chains: Phase = []
    if clean is not None:
        chains.append([step("scenes-clean", [PY, "tools/scenes.py", "-j", JOBS, *verify, *clean])])
    if native is not None:
        chains.append([step("scenes-none", [PY, "tools/scenes.py", "--clean", "none", "-j", JOBS, *verify, *native])])
    return chains


def driven_chains(clean: list[str] | None, native: list[str] | None) -> Phase:
    """The driven checks (tools/driven.py), as scene_chains takes them: one step that runs each
    check both ways when the two passes have the same checks, else a step for each pass, one
    after the other (a step runs as many checks at a time as the two scene passes together)."""
    run = [PY, "tools/driven.py", "-j", JOBS]
    if clean is not None and clean == native:
        return [[step("driven", [*run, *clean])]]
    chain = ([step("driven-clean", [*run, "--pass", "clean", *clean])] if clean is not None else []) + (
        [step("driven-none", [*run, "--pass", "native", *native])] if native is not None else [])
    return [chain] if chain else []


def passes(same: set[str] | None, native: set[tuple[str, int]], in_clean: set[tuple[str, int]]) -> tuple[bool, bool]:
    """Which of the two passes a change to functions needs: (with every Clean function, with
    Native alone). `same`: the parts of the PC code that are the base's (same_parts; None: not
    known, both passes); `native`: the functions the change touches through src/ or include/;
    `in_clean`: the functions whose Native code can run in a run with every Clean function
    (tools/fingerprint.py, native_in_clean).

    The program of a run with Native alone is the runtime, the Native objects and their tables:
    when those are the base's, so is every such run, whatever the Clean code became. The program
    of a run with every Clean function has the Native objects too, but a function with a Clean
    version never runs its Native code there. So when the Clean objects and tables are the
    base's, the Native tables too (which functions are Native, how each is called, where its
    data is), and every function the change touches has a Clean version, such a run executes
    nothing that changed. A change to the Native tables, or Native objects that differ with no
    source to say which functions changed, needs both."""
    if same is None or "native_tables" not in same:
        return True, True
    native_same = "native_objects" in same
    clean_same = {"clean_objects", "clean_tables"} <= same
    reached = not native_same and (not native or bool(native & in_clean))
    return (not clean_same or reached), not native_same


def unit_chains() -> Phase:
    """The tools' own tests, in two chains side by side: tools/test_native_statics.py takes about
    as long as all the others together (185 s of 400)."""
    steps = [step(f"unit-{t.stem}", [PY, str(t.relative_to(C.ROOT))]) for t in sorted((C.ROOT / "tools").glob("test_*.py"))]
    long = [s for s in steps if s[0] == "unit-test_native_statics"]
    return [chain for chain in ([s for s in steps if s not in long], long) if chain]


def matching_chain() -> Chain:
    """The checks of the matching sources a change to src/, include/ or the symbol tables needs
    (CI runs them on every push): every function compiles to the ROM's bytes and links to the
    ROM's targets, the program links to the ROM's modules (when dsd is there: INSTALL.md), and
    the link leaves each source's data where the tree says it is (runtime/native-private.txt,
    which the Native build reads: so these come before it)."""
    chain = [step("verify", [PY, "tools/verify.py", "--strict", "src"])]
    name = "dsd.exe" if os.name == "nt" else "dsd"
    found = [p for p in (os.environ.get("DSD"), C.ROOT / "build" / "tools" / name,
                         C.main_checkout() / "build" / "tools" / name) if p and pathlib.Path(p).is_file()]
    if not found:
        print("gate: no dsd (INSTALL.md): the program is not linked (tools/link.py)")
        return chain
    return [*chain, step("link", [PY, "tools/link.py"], DSD=str(found[0])),
            step("placement", ["git", "diff", "--exit-code", "--", "runtime/native-private.txt"])]


def same_parts(commit: str) -> set[str] | None:
    """The parts of this tree's PC code (tools/fingerprint.py, as the gate's step just wrote them)
    that are those of `commit`, or None when either has none (no gate passed on `commit` here
    yet, or the objects of this host are not read)."""
    import fingerprint  # noqa: PLC0415
    kept = fingerprint.load(commit)
    try:
        now = json.loads(FINGERPRINT.read_text())["parts"]
    except (OSError, ValueError, KeyError):
        now = None
    if kept is None or now is None:
        return None
    return {name for name, value in now.items() if kept.get(name) == value}


def native_in_clean() -> set[tuple[str, int]]:
    """The functions whose Native code a run with every Clean function can run, as the
    fingerprint step wrote them."""
    try:
        return {(m, int(a, 16)) for m, a in map(str.split, json.loads(FINGERPRINT.read_text())["native_in_clean"])}
    except (OSError, ValueError, KeyError):
        return set()


def plan(base: str | None, dry: bool = False, both: bool = False) -> Iterator[Phase]:
    """The phases, one after another; a phase's chains run side by side, each chain's steps in
    turn. The phases after the first are chosen once it has run (with `dry`, as far as can be
    told without it): its fingerprint step says whether the PC code is the base's. With `both`
    (--ignore-fingerprint), the choice is made as if no values were kept for the base."""
    native = [step("native", [PY, "tools/native.py"]),
              step("fingerprint", [PY, "tools/fingerprint.py", "--write", str(FINGERPRINT)])]
    lint = step("lint", [PY, "tools/lint.py"])
    # the function-level checks: the Clean functions, and the Native ones that call nothing (in a
    # runtime directory of its own, so the two run side by side)
    clean_check = step("diffcheck", [PY, "tools/diffcheck.py", "--native", "--clean"])
    native_check = step("diffcheck-native", [PY, "tools/diffcheck.py", "--native"], ACWW_RUNTIME_OUT=str(RUNTIME / "gate-check"))
    # (the tools' tests read what the Native build writes: after it, beside the function-level check)
    full = [[[clean_check], [native_check], *recording_chains(), *unit_chains()], scene_chains([], []), driven_chains([], [])]
    if base is None:
        yield [[*matching_chain(), *native], [lint]]
        yield from full
        return
    commit = affected.merge_base(base)
    paths = affected.changed_paths(commit)
    change = affected.describe(paths, commit)
    yield [[*(matching_chain() if change.matching else []), *native], [lint]]
    # A change that only renames: the PC code and its tables are the base's (every part of the
    # fingerprint), and nothing else that runs changed. The base passed its checks, and this
    # tree would run them on the same code: the tools' tests and one run of the title are enough.
    renames = affected.renames_only(paths)
    same = None if dry or both else same_parts(commit)
    if renames and same is not None and len(same) == len(PARTS):
        print(f"gate: only names changed since {commit[:12]}: the PC code is the same (tools/fingerprint.py); "
              "the tools' tests and one run")
        yield [*unit_chains(), recording_chains(native=False)[0][:1]]
        return
    if renames and dry and not both:
        print("gate: if the fingerprint step finds the PC code to be the base's (a change of names alone), the phases "
              "after the first are the tools' tests and one run; else:")
    elif renames and not both:
        print("gate: not a change of names alone: " + (f"no gate has passed on {commit[:12]} in this cache"
              if same is None else f"{', '.join(sorted(set(PARTS) - same))} differ from {commit[:12]}'s"))
    if change.everything:
        print(f"gate: every check ({change.everything} changed since {commit[:12]}: no list of functions bounds it)")
        yield from full
        return
    import driven as driven_checks  # noqa: PLC0415
    import scenes  # noqa: PLC0415 (its OUT follows ACWW_RUNTIME_OUT)
    # the scenes and driven checks that run a changed function, whose own files changed, or that
    # turn on a feature whose runtime source changed
    names = affected.select(list(scenes.SCENES), commit, scenes.OUT, change)
    checks = affected.select_driven(driven_checks.checks(), commit, change)
    print(f"gate: {len(names)} scenes: {' '.join(names)}")
    print(f"gate: {len(checks)} driven checks: {' '.join(checks)}")
    need = passes(same, change.native, native_in_clean())
    if change.funcs and need != (True, True):
        print("gate: " + {(True, False): "the Native objects and their tables are the base's: no pass with Native alone",
                          (False, True): "the Clean objects and tables are the base's, and every function changed has a "
                          "Clean version: no pass with the Clean functions",
                          (False, False): "the PC code is the base's: no pass for the functions"}[need])
    yield from chosen(change, names, checks, affected.own_scenes(names, change), affected.own_driven(checks, change),
                      need, clean_check, native_check)


def chosen(change: affected.Change, names: list[str], checks: list[str], own: set[str], own_checks: set[str],
           need: tuple[bool, bool], clean_check: Step, native_check: Step) -> list[Phase]:
    """The phases after the first of a change some list bounds: the function-level checks and the
    recordings (a function changed), the tools' tests (a tool, or a runtime source outside the
    run's), another program's own check, then the scenes `names`, then the driven checks
    `checks`. `need` (passes) says which pass the changed functions need, with every Clean
    function and with Native alone: the function-level check, the recordings, the scenes and
    the driven checks run that way only. The scenes `own` and driven checks `own_checks` (their
    own files changed, or a runtime source their runs enter) run both ways."""
    clean, native = need
    programs = "diffcheck" in change.programs
    functions = ([[clean_check]] if (change.funcs and clean) or programs else []) + (
        [[native_check]] if (change.native and native) or programs else [])
    recordings = recording_chains(native=change.recordings or (bool(change.funcs) and native),
                                  clean=change.recordings or (bool(change.funcs) and clean))
    # the front end builds where the recordings with Clean code do: after them
    play = [step("play-build", [PY, "tools/play.py", "--build-only"], ACWW_RUNTIME_OUT=str(RUNTIME / "gate-clean"))
            ] if "play" in change.programs and os.name == "nt" else []
    if recordings and recordings[-1][0][0].endswith("-clean"):
        recordings[-1] = [*recordings[-1], *play]
    elif play:
        recordings.append(play)
    first = functions + recordings + (unit_chains() if change.tools else [])

    def kept(listed: list[str], always: set[str], wanted: bool) -> list[str] | None:
        return [n for n in listed if wanted or n in always] or None
    return [phase for phase in (first, scene_chains(kept(names, own, clean), kept(names, own, native)),
                                driven_chains(kept(checks, own_checks, clean), kept(checks, own_checks, native))) if phase]


def keep_parts() -> None:
    """After a gate that passed: this tree's parts kept under its commit (tools/fingerprint.py,
    record), for the gates of the changes that start from it. Only a tree with nothing
    uncommitted, when the fingerprint was taken and now, has a commit to keep them under."""
    import fingerprint  # noqa: PLC0415
    try:
        found = json.loads(FINGERPRINT.read_text())
    except (OSError, ValueError):
        return
    if found.get("parts") and found.get("commit") and found["commit"] == fingerprint.head():
        fingerprint.record(found["commit"], found["parts"])
        print(f"gate: the PC code's fingerprint is kept for {found['commit'][:12]}")


def main() -> int:
    args = sys.argv[1:]
    flags = {a for a in args if a.startswith("--")}
    unknown = flags - {"--full", "--dry-run", "--keep-going", "--ignore-fingerprint"}
    if unknown:
        raise SystemExit(f"gate: unknown option {' '.join(sorted(unknown))}")
    rest = [a for a in args if a not in flags]
    base = None if "--full" in flags else (rest[0] if rest else "main")
    keep_going = "--keep-going" in flags
    logs = C.BUILD / "gate"
    logs.mkdir(parents=True, exist_ok=True)
    failed: list[str] = []
    left_out: list[str] = []
    printing = threading.Lock()
    stop = logs / "stop"  # made at the first failure, by this tool or by a step (C.gate_stop)
    env = dict(os.environ)
    env.pop("ACWW_GATE_STOP", None)
    if not keep_going:
        env["ACWW_GATE_STOP"] = str(stop)

    def stopped() -> bool:
        return not keep_going and (bool(failed) or stop.exists())

    def chain(steps: Chain) -> None:
        for name, cmd, extra in steps:
            if stopped():
                with printing:
                    left_out.append(name)
                continue
            start = time.time()
            with open(logs / f"{name}.log", "w", encoding="utf-8", errors="replace") as out:
                status = subprocess.run(cmd, cwd=C.ROOT, stdout=out, stderr=subprocess.STDOUT,
                                        env={**env, **extra}).returncode
            tail = (logs / f"{name}.log").read_text(encoding="utf-8", errors="replace").strip().splitlines()[-1:]
            with printing:
                print(f"{'ok  ' if status == 0 else 'FAIL'} {name} ({time.time() - start:.0f} s) {tail[0] if tail else ''}",
                      flush=True)
                if status:
                    failed.append(name)
                    if not keep_going:
                        stop.touch()
    started = time.time()
    if "--dry-run" in flags:
        for i, phase in enumerate(plan(base, dry=True, both="--ignore-fingerprint" in flags), 1):
            print(f"gate: phase {i}: " + " | ".join(", ".join(name for name, _, _ in steps) for steps in phase))
        return 0
    stop.unlink(missing_ok=True)
    FINGERPRINT.unlink(missing_ok=True)
    for phase in plan(base, both="--ignore-fingerprint" in flags):
        with cf.ThreadPoolExecutor(len(phase)) as pool:
            list(pool.map(chain, phase))
        if stopped():
            break  # (the phases after it are chosen from what this one found)
    if left_out:
        print(f"gate: not run after the failure: {', '.join(left_out)}")
    if not failed:
        keep_parts()
    print(f"gate: {'failed: ' + ', '.join(failed) if failed else 'every step passed'} ({time.time() - started:.0f} s)")
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())
