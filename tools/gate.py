"""The checks a change needs before it is committed, chosen from what it changed (tools/affected.py).

    python tools/gate.py               # the checks a change since main needs
    python tools/gate.py BASE          # ... since BASE
    python tools/gate.py --full        # every check
    python tools/gate.py --dry-run     # only say which checks would run
    python tools/gate.py --keep-going  # do not stop at the first failure

A change that only adds or changes scenes (recordings, expected frames, tools/scenes.py's
tables) runs those scenes both ways (all Clean, and Native alone) and the lint. A change to
sources in src/, include/ or clean/ also runs the function-level check and the two recordings
both ways, the scenes whose functions it touches and the driven checks (tools/driven.py); a
change that adds or changes driven checks runs those. Anything else (runtime/, tools/, config/)
runs every check. The seed save comes from ACWW_SCENE_SEED, as for tools/scenes.py. Each step's
output goes to build/<version>/gate/<step>.log (build/adm-kr/gate by default, tools/versions.py);
the exit status is 1 when a step failed.

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
import os
import pathlib
import subprocess
import sys
import threading
import time

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


def plan(base: str | None) -> list[Phase]:
    """Phases run one after another; a phase's chains run side by side, each chain's steps in turn."""
    native = [step("native", [PY, "tools/native.py"])]
    lint = step("lint", [PY, "tools/lint.py"])
    diffcheck = [step("diffcheck", [PY, "tools/diffcheck.py", "--native", "--clean"])]

    def driven(names: list[str]) -> Phase:
        return [[step("driven", [PY, "tools/driven.py", "-j", JOBS, *names])]]
    # (the tools' tests read what the Native build writes: after it, beside the function-level check)
    full = [[native, [lint]], [diffcheck, *recording_chains(), unit_steps()], scene_chains([]), driven([])]
    if base is None:
        return full
    paths = affected.changed_paths(base)
    funcs, own = affected.functions_of(paths, base)
    if funcs is affected.EVERYTHING:
        print(f"gate: every check (a change since {base} outside src/, include/, clean/ and the scenes)")
        return full
    import scenes  # noqa: PLC0415 (its OUT follows ACWW_RUNTIME_OUT)
    # with no function changed only the scenes whose own entries changed can differ
    names = affected.select(list(scenes.SCENES), base, scenes.OUT) if funcs else sorted(own & set(scenes.SCENES))
    print(f"gate: {len(names)} scenes: {' '.join(names)}")
    phases = [[native, [lint]]]
    if funcs:
        phases.append([diffcheck, *recording_chains()])
    if names:
        phases.append(scene_chains(names))
    # the driven checks (tools/driven.py): every one when a function changed, else those changed
    changed = sorted(pathlib.PurePosixPath(p).stem for p in paths
                     if p.startswith(f"{REC}/driven/") and (C.ROOT / p).exists())
    if funcs or changed:
        phases.append(driven([] if funcs else changed))
    return phases


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
    phases = plan(base)
    if "--dry-run" in flags:
        for i, phase in enumerate(phases, 1):
            print(f"gate: phase {i}: " + " | ".join(", ".join(name for name, _, _ in steps) for steps in phase))
        return 0
    stop.unlink(missing_ok=True)
    for phase in phases:
        with cf.ThreadPoolExecutor(len(phase)) as pool:
            list(pool.map(chain, phase))
    if left_out:
        print(f"gate: not run after the failure: {', '.join(left_out)}")
    print(f"gate: {'failed: ' + ', '.join(failed) if failed else 'every step passed'} ({time.time() - started:.0f} s)")
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())
