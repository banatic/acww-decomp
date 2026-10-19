"""Play scenes from a town save and check that Native and Clean code behave as the ROM's code does
(docs/runtime.md, scene-level checks). Local only: the scenes start from a save of a played town,
which is not part of this repository.

    python tools/scenes.py --list
    python tools/scenes.py --seed PATH                       # every scene, Native+Clean vs Reference
    python tools/scenes.py --seed PATH fish-cast tool-axe    # some of them
    python tools/scenes.py --seed PATH -j 4                  # four scenes at a time
    python tools/scenes.py --seed PATH --look fish-cast      # Reference only, PNGs of its key frames
    python tools/scenes.py --seed PATH --bisect house       # which Clean function breaks a scene
    python tools/scenes.py --convert SCRIPT.pad --at 3000:2400   # a pad script as a recording

The seed save (or ACWW_SCENE_SEED) is a 256 KB flash image of a town with one player, checked by
its SHA-256 (SEED_SHA256); it is only read. Each scene's save is the seed with a few fields
changed (SAVES: the held item, the money, the pockets) and its checksum made good again; the
derived saves are written under the run directory (build/, never committed).

A scene is an input recording in runtime/recordings/scenes/ (format: runtime/input.h): the boot
from the title through the continue menu into the town, then what the scene plays. Each runs with
`tools/run.py --native=all --clean --save ... --rtc RTC --ram-hash ...` (--native and --clean
choose other lists; `--clean none` runs Native alone): a Reference run, then a
Native run with every Clean function in place, compared frame by frame and in memory at the
scene's checkpoints. A scene passes when tools/run.py says "Native and Reference agree" (and, with
a <scene>.sha1 file beside the recordings, when the frames are the expected ones: SHA-1s of
frames only, no bytes of the save).

The recordings were converted from the port project's pad scripts (`--convert`): rows
`<frame> <mask> <frames>` hold a button mask (A=1 B=2 SELECT=4 START=8 RIGHT=16 LEFT=32 UP=64
DOWN=128 R=256 L=512 X=0x400 Y=0x800) for some frames, `<frame> T <x> <y> <frames>` the pen;
overlapping button rows are ORed, the first matching pen row wins. `--at FROM:TO` moves the rows
that start at FROM to TO (the runtimes reach the town at different frames).
"""

from __future__ import annotations

import argparse
import concurrent.futures as cf
import hashlib
import os
import pathlib
import queue
import re
import struct
import subprocess
import sys
import time

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import common as C  # noqa: E402

RECORDINGS = C.ROOT / "runtime" / "recordings" / "scenes"
OUT = (pathlib.Path(os.environ["ACWW_RUNTIME_OUT"]) if os.environ.get("ACWW_RUNTIME_OUT")
       else C.BUILD / ("runtime" if os.name == "nt" else "runtime-linux")) / "scenes"
SEED_SHA256 = "360e704aedca89b1cc70d17a1e922b15da3d48515e9299b858f6c2b9e703b0fc"
RTC = "2026-09-11 11:30:00"

# The save: two copies of the town (banks) of 0x173fc bytes, each with a 16-bit checksum at
# 0x173f8 that makes the sum of the bank's halfwords zero; the game writes the second as a copy
# of the first.
BANK_SIZE = 0x173FC
CHECKSUM = 0x173F8

# Saves derived from the seed: name -> [(offset in bank 1, struct format, value)].
HELD = 0x241A          # the player's held item
MONEY = 0x1C24         # the player's wallet
POCKETS = 0x14 + 0x1BF2  # the player's pockets, 15 halfwords
SAVES = {
    "seed": [],
    "rod": [(HELD, "<H", 0x1374)],                         # the fishing rod
    "rich": [(HELD, "<H", 0x1374), (MONEY, "<I", 30000)],  # ... and 30,000 bells
    "axe": [(HELD, "<H", 0x136B)],
    "net": [(HELD, "<H", 0x1376)],
    "shovel": [(HELD, "<H", 0x1369)],
    # pockets 0 and 1: a piece of furniture (0x3508) and a hat (0x4000)
    "furni": [(POCKETS, "<H", 0x3508), (POCKETS + 2, "<H", 0x4000)],
}

# name -> save, recording (runtime/recordings/scenes/<name>.txt), frames to run, memory
# checkpoints, the frames that show the scene's intent (--look), and what that is.
SCENES: dict[str, dict] = {}


def scene(name: str, save: str, frames: int, ram: list[int], look: list[int], intent: str,
          recording: str | None = None, rtc: str = RTC) -> None:
    SCENES[name] = dict(save=save, recording=recording or name, frames=frames, ram=ram, look=look,
                        intent=intent, rtc=rtc)


def frames(a: int, b: int, step: int) -> list[int]:
    return list(range(a, b + 1, step))


scene("fish-cast", "rod", 4200, [2600, 3500, 4199], frames(2700, 4200, 50),
      "walk to the river, cast the rod into the water, reel in")
scene("tool-axe", "axe", 3700, [2600, 3200, 3699], frames(2700, 3700, 30),
      "swing the axe facing south, east, west and north", "tools")
scene("tool-shovel", "shovel", 3700, [2600, 3200, 3699], frames(2700, 3700, 30),
      "dig with the shovel facing south, east, west and north", "tools")
scene("tool-net", "net", 3700, [2600, 3200, 3699], frames(2700, 3700, 30),
      "swing the bug net facing south, east, west and north", "tools")
scene("villager-talk", "seed", 4900, [2600, 4100, 4500, 4899], frames(4000, 4900, 50),
      "walk up to a villager and talk to it")
scene("fish-carry", "rod", 3100, [2600, 2900, 3099], frames(2700, 3100, 50),
      "walk south carrying the rod")
scene("fish-night", "rod", 4000, [2600, 3500, 3999], frames(3400, 4000, 50),
      "fish-cast at night", "fish-cast", "2026-09-11 21:30:00")
scene("shop-talk", "rich", 5100, [2600, 3800, 4500, 5099], frames(2900, 5100, 100),
      "walk into Nook's shop, talk to him, open the sell window")
scene("house", "rod", 4200, [2600, 3400, 4199], frames(2700, 4200, 50),
      "walk into the player's house")
scene("house-exit", "rod", 4200, [2600, 3400, 4199], frames(2700, 4200, 50),
      "walk into the player's house and out again")
scene("able-sisters", "rod", 4700, [2600, 3600, 4699], frames(2900, 4700, 50),
      "walk into the Able Sisters' shop, Mabel greets the player")
scene("pockets", "seed", 3500, [2600, 3000, 3499], frames(2700, 3500, 50),
      "open the pockets, drag the work clothes onto the player to wear them")
scene("pockets-furni", "furni", 3200, [2600, 2900, 3199], frames(2700, 3200, 50),
      "open the pockets holding a piece of furniture and a hat, close")


# ------------------------------------------------------------------------------ saves

def bank_checksum(bank: bytes) -> int:
    total = sum(struct.unpack_from(f"<{BANK_SIZE // 2}H", bank)) - struct.unpack_from("<H", bank, CHECKSUM)[0]
    return -total & 0xFFFF


def derive_save(seed: pathlib.Path, name: str) -> pathlib.Path:
    data = bytearray(seed.read_bytes())
    if hashlib.sha256(data).hexdigest() != SEED_SHA256:
        raise SystemExit(f"{seed}: not the seed save (SHA-256 {SEED_SHA256})")
    for offset, fmt, value in SAVES[name]:
        struct.pack_into(fmt, data, offset, value)
    if SAVES[name]:
        struct.pack_into("<H", data, CHECKSUM, bank_checksum(bytes(data[:BANK_SIZE])))
        data[BANK_SIZE:2 * BANK_SIZE] = data[:BANK_SIZE]
    out = OUT / "saves" / f"{name}.sav"
    out.parent.mkdir(parents=True, exist_ok=True)
    if not out.exists() or out.read_bytes() != data:
        out.write_bytes(bytes(data))
    return out


# ------------------------------------------------------------------------------ recordings

KEYS = ("A", "B", "SELECT", "START", "RIGHT", "LEFT", "UP", "DOWN", "R", "L", "X", "Y")


def keys_text(mask: int) -> str:
    return "+".join(k for i, k in enumerate(KEYS) if mask >> i & 1) or "-"


def convert(text: str, moves: list[tuple[int, int]]) -> str:
    """A pad script as recording lines; `moves` [(from, to)]: rows from `from` on move by to-from
    (the last move whose `from` a row reaches applies)."""
    pad, pen = [], []
    for line in text.splitlines():
        line = line.split("#")[0].split()
        if not line:
            continue
        frame = int(line[0], 0)
        shift = 0
        for start, to in sorted(moves):
            if frame >= start:
                shift = to - start
        if line[1] == "T":
            pen.append((frame + shift, int(line[4], 0), int(line[2], 0), int(line[3], 0)))
        else:
            pad.append((frame + shift, int(line[2], 0), int(line[1], 0)))
    ends = [f + n for f, n, _ in pad] + [f + n for f, n, _, _ in pen]
    out, last = [], None
    for frame in range(min(f for f, *_ in pad + pen), max(ends) + 1):
        mask = 0
        for f, n, m in pad:
            if f <= frame < f + n:
                mask |= m
        touch = next((f"{x},{y}" for f, n, x, y in pen if f <= frame < f + n), "-")
        state = (keys_text(mask), touch)
        if state != last:
            out.append(f"{frame} {state[0]} {state[1]}")
            last = state
    return "\n".join(out) + "\n"


# ------------------------------------------------------------------------------ runs

def run(name: str, seed: pathlib.Path, look: bool, only_native: str, clean: str | None,
        runtime: pathlib.Path | None = None) -> dict:
    """One scene's run; with `runtime`, tools/run.py builds and runs there (ACWW_RUNTIME_OUT), so
    scenes can run side by side: each one's runs write their programs and logs in one place."""
    sc = SCENES[name]
    recording = RECORDINGS / f"{sc['recording']}.txt"
    save = derive_save(seed, sc["save"])
    work = OUT / name
    work.mkdir(parents=True, exist_ok=True)
    cmd = [sys.executable, str(C.ROOT / "tools" / "run.py"), "0", str(sc["frames"]), "--input", str(recording),
           "--rtc", sc["rtc"], "--save", str(save)]
    if look:
        cmd += ["--png", str(work / "png"), "--frames", ",".join(map(str, sc["look"]))]
    else:
        cmd += ["--native", only_native, *([f"--clean={clean}"] if clean else []),
                "--ram-hash", ",".join(map(str, sc["ram"])), "--hash", str(work / "hashes.txt")]
        expect = RECORDINGS / f"{name}.sha1"
        if expect.exists():
            cmd += ["--expect", str(expect)]
    started = time.monotonic()
    env = dict(os.environ, ACWW_RUNTIME_OUT=str(runtime)) if runtime else None
    p = subprocess.run(cmd, cwd=C.ROOT, capture_output=True, text=True, errors="replace", env=env)
    text = p.stdout + p.stderr
    (work / ("look.log" if look else "run.log")).write_text(text, encoding="utf-8")
    result = dict(name=name, status=p.returncode, seconds=round(time.monotonic() - started), log=text)
    m = re.search(r"native: (\d+) Clean functions in place of their Native ones, (\d+) entered from the interpreter",
                  text)
    result["clean"] = (int(m.group(1)), int(m.group(2))) if m else None
    m = re.search(r"frames: reference (\w+), native (\w+)", text)
    result["frames"] = m.group(1) if m else None
    result["agree"] = "Native and Reference agree" in text
    result["first"] = None
    if not look:
        # tools/run.py leaves both runs' logs and frame hashes in one place for every run: keep
        # this scene's, and name the first frame the two runs show differently
        run_dir = (runtime or OUT.parent) / "native-run"
        for log in ("reference.log", "native.log", "reference-hashes.txt"):
            if (run_dir / log).exists():
                (work / log).write_bytes((run_dir / log).read_bytes())
        ref, nat = (frame_hashes(work / n) for n in ("reference-hashes.txt", "hashes.txt"))
        result["first"] = next((f for f in sorted(ref) if ref[f] != nat.get(f)), None)
    return result


def frame_hashes(path: pathlib.Path) -> dict[int, str]:
    """`frame <n> <upper> <lower>` lines (tools/run.py --hash) by frame."""
    out = {}
    for line in path.read_text().splitlines() if path.exists() else []:
        parts = line.split()
        if len(parts) == 4 and parts[0] == "frame":
            out[int(parts[1])] = parts[2] + " " + parts[3]
    return out


def bisect(name: str, seed: pathlib.Path, native: str, skip: set[str]) -> None:
    """Halve the Clean functions (by source file, then one by one) until one is left whose Clean
    version makes the scene differ; assumes one such function (the others agree without it). The
    functions in `skip` (ones already found) stay Native throughout."""
    files = {}
    for path in sorted((C.ROOT / "clean").rglob("*.c")):
        names = [plain or quoted for plain, quoted in
                 re.findall(r"^CLEAN_AS(?:\((\w+)|_SYMBOL\(\"([^\"]+)\"),", path.read_text(encoding="utf-8"), re.M)
                 if (plain or quoted) not in skip]
        if names:
            files[path.relative_to(C.ROOT).as_posix()] = names
    listed = OUT / "bisect.txt"

    def agrees(names: list[str]) -> bool:
        listed.parent.mkdir(parents=True, exist_ok=True)
        listed.write_text("".join(f"{n}\n" for n in names) or "nothing\n")
        r = run(name, seed, False, native, str(listed))
        print(f"  {len(names)} Clean functions: {'agree' if r['agree'] else 'DIFFER'}", flush=True)
        return r["agree"]

    def search(items: list, expand) -> object:
        while len(items) > 1:
            half = items[:len(items) // 2]
            items = half if not agrees([n for i in half for n in expand(i)]) else items[len(items) // 2:]
        return items[0]

    if agrees([n for names in files.values() for n in names]):
        print(f"{name}: agrees with every Clean function")
        return
    if not agrees([]):
        print(f"{name}: differs with Native code alone (no Clean function): not a Clean function's doing")
        return
    path = search(list(files), lambda f: files[f])
    print(f"{name}: {path}", flush=True)
    function = search(files[path], lambda n: [n])
    print(f"{name}: {function} ({path})")


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("scenes", nargs="*")
    ap.add_argument("--seed", default=os.environ.get("ACWW_SCENE_SEED"), help="the seed save (read only)")
    ap.add_argument("--list", action="store_true")
    ap.add_argument("--look", action="store_true", help="Reference only, PNGs of the key frames")
    ap.add_argument("--native", default="all", help="the --native policy for tools/run.py (default all)")
    ap.add_argument("--clean", default="all", help="the --clean list for tools/run.py (default all; 'none': Native only)")
    ap.add_argument("--bisect", action="store_true", help="find the Clean function that breaks each scene")
    ap.add_argument("--skip", default="", help="with --bisect: functions (comma-separated) left Native")
    ap.add_argument("-j", "--jobs", type=int, default=1, help="scenes run at a time (each in a runtime "
                    "directory of its own under the scenes', built the first time)")
    ap.add_argument("--convert", metavar="PAD", help="print a pad script as a recording")
    ap.add_argument("--at", default="", help="with --convert: FROM:TO[,FROM:TO...] moves rows")
    args = ap.parse_args()
    if args.convert:
        moves = [tuple(int(v) for v in m.split(":")) for m in args.at.split(",") if m]
        sys.stdout.write(convert(pathlib.Path(args.convert).read_text(), moves))
        return 0
    if args.list:
        for name, sc in SCENES.items():
            print(f"{name:14} save={sc['save']:7} frames={sc['frames']:5}  {sc['intent']}")
        return 0
    if not args.seed:
        raise SystemExit("name the seed save with --seed or ACWW_SCENE_SEED")
    seed = pathlib.Path(args.seed)
    names = args.scenes or list(SCENES)
    unknown = [n for n in names if n not in SCENES]
    if unknown:
        raise SystemExit(f"unknown scenes {unknown}; --list")
    if args.bisect:
        for name in names:
            bisect(name, seed, args.native, set(filter(None, args.skip.split(","))))
        return 0
    clean = None if args.clean == "none" else args.clean
    if args.jobs > 1:
        for sc in dict.fromkeys(SCENES[n]["save"] for n in names):  # written once, before the runs read them
            derive_save(seed, sc)
        slots = queue.Queue()
        for i in range(args.jobs):
            slots.put(OUT / f".runtime-{i}")

        def one(name: str) -> dict:
            runtime = slots.get()
            try:
                return run(name, seed, args.look, args.native, clean, runtime)
            finally:
                slots.put(runtime)
        pool = cf.ThreadPoolExecutor(args.jobs)
        pending = [pool.submit(one, n) for n in names]
    results = []
    for i, name in enumerate(names):
        print(f"{name}...", flush=True)
        r = pending[i].result() if args.jobs > 1 else run(name, seed, args.look, args.native, clean)
        results.append(r)
        if args.look:
            print(f"  {r['status']=} pngs in {(OUT / name / 'png').as_posix()} ({r['seconds']} s)")
            continue
        clean = f", {r['clean'][1]} of {r['clean'][0]} Clean functions entered from the interpreter" if r["clean"] else ""
        print(f"  {'PASS' if r['agree'] and r['status'] == 0 else 'FAIL'}: frames {r['frames']}{clean} "
              f"({r['seconds']} s; log {(OUT / name / 'run.log').as_posix()})", flush=True)
        if r["first"] is not None:
            print(f"    the frames first differ at frame {r['first']}")
        for line in r["log"].splitlines():
            if "DIVERGED" in line or "DIFFERENT" in line or line.startswith("native run: stop"):
                print(f"    {line}")
    if args.look:
        return 0
    failed = [r["name"] for r in results if not (r["agree"] and r["status"] == 0)]
    print(f"scenes: {len(results) - len(failed)} of {len(results)} agree" + (f"; failed {failed}" if failed else ""))
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())
