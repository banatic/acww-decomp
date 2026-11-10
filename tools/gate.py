"""The checks a change needs before it is committed, chosen from what it changed (tools/affected.py).

    python tools/gate.py               # the checks a change since main needs
    python tools/gate.py BASE          # ... since BASE
    python tools/gate.py --full        # every check
    python tools/gate.py --dry-run     # only say which checks would run
    python tools/gate.py --keep-going  # do not stop at the first failure

A change is what differs from the commit this tree left BASE at (their merge base: what BASE
gained since is not this tree's change), committed or not.

A change that only adds or changes scenes (recordings, expected frames, tools/scenes.py's
tables) runs those scenes both ways (all Clean, and Native alone) and the lint. A change to
sources in src/, include/ or clean/ also runs the function-level check and the two recordings
both ways, the scenes whose functions it touches and the driven checks (tools/driven.py); a
change that adds or changes driven checks runs those. Anything else (runtime/, tools/, config/)
runs every check. A change to src/, include/ or config/ first checks the matching sources as CI
does: tools/verify.py (every function of src/ ok), tools/link.py, and that the link leaves
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


def scene_chains(names: list[str], native: bool = True, clean: bool = True) -> Phase:
    """The two passes, each a chain of its own (they run side by side)."""
    # a few of each pass's cached Reference runs are made again: a key that leaves out something
    # a run depends on shows as a failed step (tools/run.py, ACWW_REFERENCE_VERIFY)
    verify = ["--verify-cache", VERIFY]
    chains: Phase = []
    if clean:
        chains.append([step("scenes-clean", [PY, "tools/scenes.py", "-j", JOBS, *verify, *names])])
    if native:
        chains.append([step("scenes-none", [PY, "tools/scenes.py", "--clean", "none", "-j", JOBS, *verify, *names])])
    return chains


def unit_steps() -> Chain:
    return [step(f"unit-{t.stem}", [PY, str(t.relative_to(C.ROOT))]) for t in sorted((C.ROOT / "tools").glob("test_*.py"))]


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


def plan(base: str | None, dry: bool = False) -> Iterator[Phase]:
    """The phases, one after another; a phase's chains run side by side, each chain's steps in
    turn. The phases after the first are chosen once it has run (with `dry`, as far as can be
    told without it): its fingerprint step says whether the PC code is the base's."""
    native = [step("native", [PY, "tools/native.py"]),
              step("fingerprint", [PY, "tools/fingerprint.py", "--write", str(FINGERPRINT)])]
    lint = step("lint", [PY, "tools/lint.py"])
    diffcheck = [step("diffcheck", [PY, "tools/diffcheck.py", "--native", "--clean"])]

    def driven(names: list[str]) -> Phase:
        return [[step("driven", [PY, "tools/driven.py", "-j", JOBS, *names])]]
    # (the tools' tests read what the Native build writes: after it, beside the function-level check)
    full = [[diffcheck, *recording_chains(), unit_steps()], scene_chains([]), driven([])]
    if base is None:
        yield [[*matching_chain(), *native], [lint]]
        yield from full
        return
    commit = affected.merge_base(base)
    paths = affected.changed_paths(commit)
    funcs, own = affected.functions_of(paths, commit)
    matching = any(p.startswith(("src/", "include/", "config/")) for p in paths)
    yield [[*(matching_chain() if matching else []), *native], [lint]]
    # A change that only renames: the PC code and its tables are the base's (every part of the
    # fingerprint), and nothing else that runs changed. The base passed its checks, and this
    # tree would run them on the same code: the tools' tests and one run of the title are enough.
    renames = affected.renames_only(paths)
    same = None if dry else same_parts(commit)
    if renames and same is not None and len(same) == len(PARTS):
        print(f"gate: only names changed since {commit[:12]}: the PC code is the same (tools/fingerprint.py); "
              "the tools' tests and one run")
        yield [unit_steps(), recording_chains(native=False)[0][:1]]
        return
    if renames and not dry:
        print("gate: not a change of names alone: " + (f"no gate has passed on {commit[:12]} in this cache"
              if same is None else f"{', '.join(sorted(set(PARTS) - same))} differ from {commit[:12]}'s"))
    if funcs is affected.EVERYTHING:
        print(f"gate: every check (a change since {commit[:12]} outside src/, include/, clean/ and the scenes)")
        yield from full
        return
    import scenes  # noqa: PLC0415 (its OUT follows ACWW_RUNTIME_OUT)
    # with no function changed only the scenes whose own entries changed can differ
    names = affected.select(list(scenes.SCENES), commit, scenes.OUT) if funcs else sorted(own & set(scenes.SCENES))
    print(f"gate: {len(names)} scenes: {' '.join(names)}")
    if funcs:
        yield [diffcheck, *recording_chains()]
    if names:
        yield scene_chains(names)
    # the driven checks (tools/driven.py): every one when a function changed, else those changed
    changed = sorted(pathlib.PurePosixPath(p).stem for p in paths
                     if p.startswith(f"{REC}/driven/") and (C.ROOT / p).exists())
    if funcs or changed:
        yield driven([] if funcs else changed)


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
    unknown = flags - {"--full", "--dry-run", "--keep-going"}
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
        for i, phase in enumerate(plan(base, dry=True), 1):
            print(f"gate: phase {i}: " + " | ".join(", ".join(name for name, _, _ in steps) for steps in phase))
        return 0
    stop.unlink(missing_ok=True)
    FINGERPRINT.unlink(missing_ok=True)
    for phase in plan(base):
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
