"""The checks a change needs before it is committed, chosen from what it changed (tools/affected.py).

    python tools/gate.py            # the checks a change since main needs
    python tools/gate.py BASE       # ... since BASE
    python tools/gate.py --full     # every check

A change that only adds or changes scenes (recordings, expected frames, tools/scenes.py's
tables) runs those scenes both ways (all Clean, and Native alone) and the lint. A change to
sources in src/, include/ or clean/ also runs the function-level check and the two recordings
both ways, and the scenes whose functions it touches. Anything else (runtime/, tools/, config/)
runs every check. The seed save comes from ACWW_SCENE_SEED, as for tools/scenes.py. Each step's
output goes to build/adm-kr/gate/<step>.log; the exit status is 1 when a step failed.

The two scene passes and the chain of the function-level check and the recordings run at the
same time: they build and run in directories of their own (tools/scenes.py locks its runtime
directories, and keeps Native alone's logs apart). A scene uses about one and a half CPUs; each
pass runs three eighths of the CPUs' count of scenes at a time (6 of 16: on 24 scenes 4 a pass
took 908 s, 6 took 731 s, with another tree's gate running; ACWW_GATE_JOBS sets it).
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
RECORDINGS = [
    ("title", "runtime/recordings/title-start", 1300, "100,390,500,700,1000,1299"),
    ("new-game", "runtime/recordings/new-game", 13760, "1299,2600,7200,9750,12100,13300,13759"),
]


def recording_steps() -> list[tuple[str, list[str]]]:
    steps = []
    for name, rec, frames, ram in RECORDINGS:
        base = [PY, "tools/run.py", "0", str(frames), "--input", f"{rec}.txt", "--rtc", RTC, "--native=all",
                "--ram-hash", ram, "--expect", f"{rec}.sha1"]
        steps += [(f"{name}-native", base), (f"{name}-clean", base + ["--clean"])]
    return steps


Step = tuple[str, list[str]]


def scene_steps(names: list[str]) -> list[list[Step]]:
    """The two passes, each a chain of its own (they run side by side)."""
    return [[("scenes-clean", [PY, "tools/scenes.py", "-j", JOBS, *names])],
            [("scenes-none", [PY, "tools/scenes.py", "--clean", "none", "-j", JOBS, *names])]]


def plan(base: str | None) -> list[list[list[Step]]]:
    """Phases run one after another; a phase's chains run side by side, each chain's steps in turn."""
    native = [[("native", [PY, "tools/native.py"])]]
    lint = ("lint", [PY, "tools/lint.py"])
    checks = [("diffcheck", [PY, "tools/diffcheck.py", "--native", "--clean"]), *recording_steps()]
    units = [(f"unit-{t.stem}", [PY, str(t.relative_to(C.ROOT))]) for t in sorted((C.ROOT / "tools").glob("test_*.py"))]
    full = [native, [checks, *scene_steps([])], [[lint, *units]]]
    if base is None:
        return full
    funcs, own = affected.functions_of(affected.changed_paths(base), base)
    if funcs is affected.EVERYTHING:
        print(f"gate: every check (a change since {base} outside src/, include/, clean/ and the scenes)")
        return full
    import scenes  # noqa: PLC0415 (its OUT follows ACWW_RUNTIME_OUT)
    # with no function changed only the scenes whose own entries changed can differ
    names = affected.select(list(scenes.SCENES), base, scenes.OUT) if funcs else sorted(own & set(scenes.SCENES))
    print(f"gate: {len(names)} scenes: {' '.join(names)}")
    together = ([checks] if funcs else []) + (scene_steps(names) if names else [])
    return [native, *([together] if together else []), [[lint]]]


def main() -> int:
    args = sys.argv[1:]
    full = "--full" in args
    rest = [a for a in args if a != "--full"]
    base = None if full else (rest[0] if rest else "main")
    logs = C.BUILD / "gate"
    logs.mkdir(parents=True, exist_ok=True)
    failed = []
    printing = threading.Lock()

    def chain(steps: list[Step]) -> None:
        for name, cmd in steps:
            start = time.time()
            with open(logs / f"{name}.log", "w", encoding="utf-8", errors="replace") as out:
                status = subprocess.run(cmd, cwd=C.ROOT, stdout=out, stderr=subprocess.STDOUT, env=os.environ).returncode
            tail = (logs / f"{name}.log").read_text(encoding="utf-8", errors="replace").strip().splitlines()[-1:]
            with printing:
                print(f"{'ok  ' if status == 0 else 'FAIL'} {name} ({time.time() - start:.0f} s) {tail[0] if tail else ''}",
                      flush=True)
                if status:
                    failed.append(name)
    started = time.time()
    for phase in plan(base):
        with cf.ThreadPoolExecutor(len(phase)) as pool:
            list(pool.map(chain, phase))
    print(f"gate: {'failed: ' + ', '.join(failed) if failed else 'every step passed'} ({time.time() - started:.0f} s)")
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())
