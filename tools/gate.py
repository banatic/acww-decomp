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
"""
from __future__ import annotations

import os
import pathlib
import subprocess
import sys
import time

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import affected  # noqa: E402
import common as C  # noqa: E402

PY = sys.executable
RTC = "2005-11-23 12:00:00"
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


def plan(base: str | None) -> list[tuple[str, list[str]]]:
    native = ("native", [PY, "tools/native.py"])
    lint = ("lint", [PY, "tools/lint.py"])
    full = [native, ("diffcheck", [PY, "tools/diffcheck.py", "--native", "--clean"]), *recording_steps(),
            ("scenes-clean", [PY, "tools/scenes.py", "-j", "4"]),
            ("scenes-none", [PY, "tools/scenes.py", "--clean", "none", "-j", "4"]), lint]
    full += [(f"unit-{t.stem}", [PY, str(t.relative_to(C.ROOT))]) for t in sorted((C.ROOT / "tools").glob("test_*.py"))]
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
    steps = [native]
    if funcs:
        steps += [("diffcheck", [PY, "tools/diffcheck.py", "--native", "--clean"]), *recording_steps()]
    if names:
        steps += [("scenes-clean", [PY, "tools/scenes.py", "-j", "4", *names]),
                  ("scenes-none", [PY, "tools/scenes.py", "--clean", "none", "-j", "4", *names])]
    return steps + [lint]


def main() -> int:
    args = sys.argv[1:]
    full = "--full" in args
    rest = [a for a in args if a != "--full"]
    base = None if full else (rest[0] if rest else "main")
    logs = C.BUILD / "gate"
    logs.mkdir(parents=True, exist_ok=True)
    failed = []
    for name, cmd in plan(base):
        start = time.time()
        with open(logs / f"{name}.log", "w", encoding="utf-8", errors="replace") as out:
            status = subprocess.run(cmd, cwd=C.ROOT, stdout=out, stderr=subprocess.STDOUT, env=os.environ).returncode
        tail = (logs / f"{name}.log").read_text(encoding="utf-8", errors="replace").strip().splitlines()[-1:]
        print(f"{'ok  ' if status == 0 else 'FAIL'} {name} ({time.time() - start:.0f} s) {tail[0] if tail else ''}",
              flush=True)
        if status:
            failed.append(name)
    print(f"gate: {'failed: ' + ', '.join(failed) if failed else 'every step passed'}")
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())
