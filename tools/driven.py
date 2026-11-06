"""Driven calls: game functions that no game path calls, run on objects alive in a scene's run
and checked both ways (docs/verification.md, "Driven calls"; runtime/driven.h).

    python tools/driven.py --list
    python tools/driven.py --seed PATH                       # every check, Clean and Native alone
    python tools/driven.py --seed PATH -j 2 aquarium-river   # some of them
    python tools/driven.py --record                          # runtime/recordings/scenes/clean-driven.txt
    python tools/driven.py --seed PATH --scout museum-halls --frames 8000,8800 \\
        --group "the aquarium fish's destructors" --slots 2,3  # the live objects for a new check

A check is a file runtime/recordings/driven/<name>.txt: an existing scene (its save, recording
and clock), how many frames the run lasts, the scene's memory checkpoints before the calls, and
the calls (runtime/driven.h: arm, call, vcall, end), with comments naming each target:

    # what it checks
    scene museum-halls
    frames 8040
    ram 7200,8000
    arm 02114c6c 021cfb98       # OS_SleepThread(the main loop's queue): between two frames
    vcall 8001 023a39cc 8 023a39cc 0 0 0 02255ea4   # ov004 AquariumSwimmer_Destruct (slot 2)

Each check runs as a scene does (tools/scenes.py): a Reference run, then the Native run with
every Clean function in place (and again with Native alone, --clean none), compared frame by
frame, in memory at the checkpoints and in memory right after each moment's calls. It passes when
tools/run.py says the two agree and both passes made the same calls (none skipped). The
functions it checked are those the calls entered in the Reference run ("driven: entered") that
ran as Clean in the Clean pass; --record writes those no scene enters
(runtime/recordings/scenes/clean-entered.txt) to clean-driven.txt, which the progress map
counts as "checked by a driven call", a level below "checked in a run".

--scout runs the scene's Reference alone with memory images at the frames given, and lists, for
each open function of a group of docs/scene-plan-groups.txt that a vtable names at one of the
slots given, the objects with that vtable at offset 0 that sit in a live block of the game's
heaps (the NNS expanded heaps' used blocks, the frame heaps' allocated ends) or in a module's
.bss, with a check's call lines for one object each.
"""
from __future__ import annotations

import argparse
import concurrent.futures as cf
import json
import os
import pathlib
import re
import struct
import subprocess
import sys
import time

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import common as C  # noqa: E402
import coverage  # noqa: E402
import scenes  # noqa: E402

CHECKS = C.ROOT / "runtime" / "recordings" / "driven"
ENTERED = C.ROOT / "runtime" / "recordings" / "scenes" / "clean-entered.txt"
DRIVEN = C.ROOT / "runtime" / "recordings" / "scenes" / "clean-driven.txt"
OUT = scenes.OUT.parent / "driven"
SNAPSHOT = 900000000  # runtime/driven.h, DRIVEN_SNAPSHOT
# where the calls are made: OS_SleepThread entered with the main loop's queue (main/main_loop.c,
# MainLoop_WaitFrame): the frame's work is done and the main thread is about to wait for the next
OS_SLEEP_THREAD, MAIN_FRAME_QUEUE = 0x02114C6C, 0x021CFB98
HEAP_SET_CURRENT = 0x020E9A08  # Heap_SetCurrent (autoload_2/heap.c)
HEAP_VTABLES = (0x0213E5B0, 0x0213E608, 0x0213E660)  # the expanded, frame and base heaps' vtables
RUN_LINES = ("arm", "call", "vcall", "end")


def read_check(name: str) -> dict:
    """A check file: its scene, frames, checkpoints, and the runtime's lines."""
    out = {"name": name, "scene": None, "frames": None, "ram": [], "lines": [], "intent": []}
    for line in (CHECKS / f"{name}.txt").read_text().splitlines():
        body = line.split("#", 1)[0].split()
        if not body:
            if line.startswith("# ") and not out["lines"]:
                out["intent"].append(line[2:])
            continue
        if body[0] == "scene":
            out["scene"] = body[1]
        elif body[0] == "frames":
            out["frames"] = int(body[1])
        elif body[0] == "ram":
            out["ram"] = [int(f) for f in body[1].split(",")]
        elif body[0] in RUN_LINES:
            out["lines"].append(line)
        else:
            raise SystemExit(f"{name}: unknown line {line!r}")
    if out["scene"] not in scenes.SCENES or not out["frames"]:
        raise SystemExit(f"{name}: needs a scene of tools/scenes.py and its frames")
    return out


def checks() -> list[str]:
    return sorted(p.stem for p in CHECKS.glob("*.txt"))


# ------------------------------------------------------------------------------ running


def run_check(name: str, seed: pathlib.Path, clean: str | None, runtime: pathlib.Path, token: str) -> dict:
    ch = read_check(name)
    sc = scenes.SCENES[ch["scene"]]
    work = OUT / name / ("clean" if clean else "native")
    work.mkdir(parents=True, exist_ok=True)
    spec = work / "calls.txt"
    spec.write_text("".join(line + "\n" for line in ch["lines"]), newline="\n")
    save = scenes.derive_save(seed, sc["save"])
    cmd = [sys.executable, str(C.ROOT / "tools" / "run.py"), "0", str(ch["frames"]), "--input",
           str(scenes.RECORDINGS / f"{sc['recording']}.txt"), "--rtc", sc["rtc"], "--save", str(save),
           *(["--sequencer"] if sc["sequencer"] else []), *(["--wireless"] if sc["wireless"] else []),
           *([f"--wifi={sc['wifi']}"] if sc["wifi"] else []),
           "--native", "all", *([f"--clean={clean}"] if clean else []), "--driven", str(spec),
           "--hash", str(work / "hashes.txt"), "--reuse-build", token]
    if ch["ram"]:
        cmd += ["--ram-hash", ",".join(map(str, ch["ram"]))]
    if clean:
        cmd += ["--clean-ran", str(work / "clean-ran.json")]
    started = time.monotonic()
    env = dict(os.environ, ACWW_RUNTIME_OUT=str(runtime))
    p = subprocess.run(cmd, cwd=C.ROOT, capture_output=True, text=True, errors="replace", env=env)
    text = p.stdout + p.stderr
    (work / "run.log").write_text(text, encoding="utf-8")
    run_dir = runtime / "native-run"
    logs = {}
    for log in ("reference.log", "native.log"):
        logs[log] = (run_dir / log).read_text(encoding="utf-8", errors="replace") if (run_dir / log).exists() else ""
        (work / log).write_text(logs[log], encoding="utf-8")
    (run_dir / "crossings.bin").unlink(missing_ok=True)
    for image in (run_dir / "ram").glob("ram-*.bin"):
        image.unlink(missing_ok=True)

    def made(log: str) -> list[str]:
        # the step a call starts at is left out: Native code before it takes no steps
        return [re.sub(r" at step \d+$", "", ln) for ln in log.splitlines()
                if re.match(r"driven: frame \d+ (call|skip)", ln)]
    ref_calls, nat_calls = made(logs["reference.log"]), made(logs["native.log"])
    moments = sorted({int(m) for m in re.findall(r"driven: frame (\d+) back at", logs["reference.log"])})
    snaps = {int(f) - SNAPSHOT: v for f, v in re.findall(r"ram after frame (\d+): .*: (same[^\n]*|DIFFERENT[^\n]*)", text)
             if int(f) >= SNAPSHOT}
    problems = []
    if "Native and Reference agree" not in text:
        problems.append("Native and Reference differ")
    if ref_calls != nat_calls:
        problems.append("the two passes made other calls")
    if any(" skip " in ln for ln in ref_calls):
        problems.append("a call was skipped (its object was not there)")
    if not ref_calls:
        problems.append("no call was made")
    for log in ("reference.log", "native.log"):
        made_calls = len(re.findall(r"driven: frame \d+ call ", logs[log]))
        returned = len(re.findall(r"driven: frame \d+ returned from ", logs[log]))
        if returned != made_calls:
            problems.append(f"{log}: {made_calls - returned} of the calls did not return (the run stopped inside one)")
    if ref_calls and not moments:
        problems.append("no moment's calls finished")
    for m in moments:
        if not snaps.get(m, "").startswith("same"):
            problems.append(f"memory after the calls of frame {m}: {snaps.get(m)}")
    return dict(name=name, clean=clean, status=p.returncode, seconds=round(time.monotonic() - started), work=work,
                calls=len(ref_calls), problems=problems, entered=entered_functions(logs["reference.log"]))


def entered_functions(log: str) -> list[tuple[str, int]]:
    """The game functions the calls entered: the "driven: entered" targets that are the start of
    a function, in the module whose image has the first 8 bytes seen there."""
    starts = function_starts()
    out = set()
    for a, w0, w1 in re.findall(r"driven: entered ([0-9a-f]{8}) ([0-9a-f]{8}) ([0-9a-f]{8})", log):
        address, head = int(a, 16), struct.pack("<II", int(w0, 16), int(w1, 16))
        for module in starts.get(address, []):
            image, base = module_image(module)
            if image[address - base:address - base + 8] == head:
                out.add((module, address))
    return sorted(out)


_starts: dict[int, list[str]] | None = None
_images: dict[str, tuple[bytes, int]] = {}


def function_starts() -> dict[int, list[str]]:
    global _starts
    if _starts is None:
        syms = C.symbol_table(C.modules())
        _starts = {}
        for module, ss in syms.by_module.items():
            for s in ss:
                if s.kind == "function":
                    _starts.setdefault(s.address & ~1, []).append(module)
    return _starts


def module_image(module: str) -> tuple[bytes, int]:
    if module not in _images:
        _images[module] = (C.module_image(module), C.modules()[module]["base"])
    return _images[module]


def clean_ran(path: pathlib.Path) -> set[tuple[str, int]]:
    if not path.exists():
        return set()
    return {(r["module"], int(r["address"], 16) if isinstance(r["address"], str) else r["address"])
            for r in json.loads(path.read_text()) if r.get("ran")}


def checked(name: str) -> list[tuple[str, int]]:
    """The functions a check's last passing runs checked: entered by its calls, run as Clean."""
    result = OUT / name / "result.json"
    return [tuple(k) for k in json.loads(result.read_text())["checked"]] if result.exists() else []


def run_all(names: list[str], seed: pathlib.Path, jobs: int) -> int:
    token = f"driven-{os.getpid()}-{time.time_ns()}"
    passes = [(n, c) for n in names for c in ("all", None)]
    runtimes = scenes.take_runtimes(min(jobs, len(passes)), "all") + scenes.take_runtimes(min(jobs, len(passes)), None)
    free = {"all": [r for r, _ in runtimes[:min(jobs, len(passes))]], None: [r for r, _ in runtimes[min(jobs, len(passes)):]]}
    import queue  # noqa: PLC0415
    pools = {k: queue.Queue() for k in free}
    for k, rs in free.items():
        for r in rs:
            pools[k].put(r)

    def one(item):
        n, c = item
        r = pools[c].get()
        try:
            return run_check(n, seed, c, r, token)
        finally:
            pools[c].put(r)
    results: dict[str, list[dict]] = {}
    with cf.ThreadPoolExecutor(max(1, jobs)) as pool:
        for res in pool.map(one, passes):
            results.setdefault(res["name"], []).append(res)
            verdict = "ok  " if not res["problems"] else "FAIL"
            print(f"{verdict} {res['name']} ({'Clean' if res['clean'] else 'Native alone'}, {res['calls']} calls, "
                  f"{res['seconds']} s){': ' + '; '.join(res['problems']) if res['problems'] else ''}", flush=True)
    failed = 0
    for n, rs in sorted(results.items()):
        ok = all(not r["problems"] for r in rs) and len(rs) == 2
        clean_pass = next(r for r in rs if r["clean"])
        ran = clean_ran(clean_pass["work"] / "clean-ran.json")
        got = [k for k in clean_pass["entered"] if k in ran]
        result = OUT / n / "result.json"
        if ok:
            result.write_text(json.dumps({"checked": got}, indent=1) + "\n")
        else:
            result.unlink(missing_ok=True)
            failed += 1
        print(f"{n}: {'passes' if ok else 'FAILS'}; its calls entered {len(clean_pass['entered'])} functions, "
              f"{len(got)} of them Clean", flush=True)
    for _, held in runtimes:
        held.close()
    return 1 if failed else 0


def record() -> int:
    entered = {(m, int(a, 16)) for m, a in (ln.split() for ln in ENTERED.read_text().splitlines()
                                            if ln and not ln.startswith("#"))}
    got: set[tuple[str, int]] = set()
    missing = []
    for name in checks():
        keys = checked(name)
        if not keys:
            missing.append(name)
        got |= set(keys)
    if missing:
        raise SystemExit(f"no passing result for {', '.join(missing)}: run them first")
    new = sorted(got - entered, key=lambda k: (k[0], k[1]))
    DRIVEN.write_text("# The Clean functions driven calls check and no scene enters (tools/driven.py --record)\n"
                      + "".join(f"{m} {a:08x}\n" for m, a in new), newline="\n")
    print(f"{DRIVEN.relative_to(C.ROOT).as_posix()}: {len(new)} functions ({len(got)} entered by driven calls)")
    return 0


# ------------------------------------------------------------------------------ scouting


class Image:
    """A Reference memory image (tools/run.py --ram-dump: ITCM, main RAM, DTCM; stacks zeroed)."""

    def __init__(self, path: pathlib.Path):
        self.data = path.read_bytes()
        self.main = self.data[0x8000:0x408000]

    def word(self, address: int) -> int:
        if 0x02000000 <= address <= 0x023FFFFC:
            return struct.unpack_from("<I", self.main, address - 0x02000000)[0]
        return 0

    def live_ranges(self) -> list[tuple[int, int, int, str]]:
        """(start, end, NNS heap, kind) of each used block of an expanded heap and the two
        allocated ends of each frame heap."""
        out = []
        for i in range(0, len(self.main), 4):
            v = struct.unpack_from("<I", self.main, i)[0]
            a = 0x02000000 + i
            if v == 0x45585048 and self.word(a + 0x18) == a + 0x38:  # 'EXPH'
                b, n = self.word(a + 0x2C), 0
                while b and n < 100000 and self.word(b) & 0xFFFF == 0x5544:  # 'UD'
                    out.append((b + 16, b + 16 + self.word(b + 4), a, "block"))
                    b, n = self.word(b + 12), n + 1
            elif v == 0x46524D48 and self.word(a + 0x18) == a + 0x30:  # 'FRMH'
                out.append((self.word(a + 0x18), self.word(a + 0x24), a, "frame"))
                out.append((self.word(a + 0x28), self.word(a + 0x1C), a, "frame"))
        return out

    def heap_objects(self) -> dict[int, int]:
        """NNS heap -> the game's Heap that owns it (autoload_2/heap.h: vtable, ..., handle)."""
        out = {}
        for i in range(0, len(self.main), 4):
            if struct.unpack_from("<I", self.main, i)[0] in HEAP_VTABLES:
                h = 0x02000000 + i
                nns = self.word(h + 0x14)
                if nns and self.word(h + 4) == nns:
                    out[nns] = h
        return out


def module_ranges() -> list[tuple[int, int, str, bool]]:
    """(start, end, module, is .bss) of the modules' images and .bss."""
    out = []
    for name, m in C.modules().items():
        out.append((m["base"], m["base"] + m["size"], name, False))
        if m.get("bss"):
            out.append((m["base"] + m["size"], m["base"] + m["size"] + m["bss"], name, True))
    return out


def open_targets(groups: list[str]) -> dict[tuple[str, int], tuple[str, str, str]]:
    """The open functions (no scene enters them) of the plan's groups: key -> (file, name, group)."""
    syms = C.symbol_table(C.modules())
    clean = coverage.clean_functions(syms)
    entered = {(m, int(a, 16)) for m, a in (ln.split() for ln in ENTERED.read_text().splitlines()
                                            if ln and not ln.startswith("#"))}
    plan_groups = coverage.read_plan(C.ROOT / "docs" / "scene-plan-groups.txt")
    out = {}
    for k, v in clean.items():
        g = coverage.group_of(plan_groups, *v) if k not in entered else None
        if g is not None and g["group"] in groups:
            out[k] = (*v, g["group"])
    return out


def vtable_slots(keys, slots: list[int]) -> dict[tuple[str, int], list[tuple[int, int]]]:
    """For each function, the (vtable, slot) pairs naming it: a word of a module's image equal to
    its address (bit 0 for Thumb) at a slot of `slots` past a vtable's start, which the two zero
    words before slot 0 mark (the game's vtables have no RTTI)."""
    syms = C.symbol_table(C.modules())
    thumb = {(s.module, s.address & ~1): s.thumb for ss in syms.by_module.values() for s in ss if s.kind == "function"}
    names: dict[int, list[tuple[str, int]]] = {}
    for key in keys:
        names.setdefault(key[1] | thumb.get(key, False), []).append(key)
    out: dict[tuple[str, int], list[tuple[int, int]]] = {}
    for module in C.modules():
        image, base = module_image(module)
        for i in range(0, len(image) - 3, 4):
            for key in names.get(struct.unpack_from("<I", image, i)[0], []):
                # an overlay's function is named by its own overlay's data or by a resident module's
                if key[0] != module and key[0].startswith("ov") and module.startswith("ov"):
                    continue
                for slot in slots:
                    v = i - 4 * slot
                    if v >= 8 and struct.unpack_from("<II", image, v - 8) == (0, 0):
                        out.setdefault(key, []).append((base + v, slot))
    return out


def dump_scene(scene: str, frames: list[int], seed: pathlib.Path, dump: pathlib.Path) -> None:
    """The scene's Reference alone, with memory images after `frames` in `dump`."""
    sc = scenes.SCENES[scene]
    dump.mkdir(parents=True, exist_ok=True)
    if all((dump / f"ram-{f}-reference.bin").exists() for f in frames):
        return
    save = scenes.derive_save(seed, sc["save"])
    cmd = [sys.executable, str(C.ROOT / "tools" / "run.py"), "0", str(max(frames) + 1), "--input",
           str(scenes.RECORDINGS / f"{sc['recording']}.txt"), "--rtc", sc["rtc"], "--save", str(save),
           *(["--sequencer"] if sc["sequencer"] else []), *(["--wireless"] if sc["wireless"] else []),
           *([f"--wifi={sc['wifi']}"] if sc["wifi"] else []),
           "--ram-hash", ",".join(map(str, frames)), "--ram-dump", str(dump)]
    env = dict(os.environ, ACWW_RUNTIME_OUT=str(dump / ".runtime"))
    subprocess.run(cmd, cwd=C.ROOT, check=True, capture_output=True, env=env)


def objects_in(img: Image, vtables: set[int]) -> dict[int, list[list[int]]]:
    """vtable -> [object, innermost live block's start, its end, the game's Heap of it (0 for a
    frame heap or .bss)] of each live object whose first word is the vtable."""
    live = img.live_ranges()
    heaps = img.heap_objects()
    mods = module_ranges()
    out: dict[int, list[list[int]]] = {}
    for i in range(0, len(img.main), 4):
        v = struct.unpack_from("<I", img.main, i)[0]
        if v not in vtables:
            continue
        o = 0x02000000 + i
        where = min(((s, e, h, k) for s, e, h, k in live if s <= o < e), key=lambda r: r[1] - r[0], default=None)
        if where is None:
            if not any(b and s <= o < e for s, e, _, b in mods) or any(not b and s <= o < e for s, e, _, b in mods):
                continue  # a word of a module's code or data, or of free memory
            out.setdefault(v, []).append([o, o, o, 0])
        else:
            out.setdefault(v, []).append([o, where[0], where[1], heaps.get(where[2], 0) if where[3] == "block" else 0])
    return out


def survey(names: list[str], groups: list[str], slots: list[int], seed: pathlib.Path, jobs: int) -> int:
    """OUT/survey/<scene>.json: at each of the scene's memory checkpoints, the live objects of the
    vtables that name the groups' open functions at those slots."""
    targets = open_targets(groups)
    vts = vtable_slots(targets, slots)
    wanted = {v for vs in vts.values() for v, _ in vs}
    print(f"{len(targets)} open functions, {sum(1 for k in targets if k in vts)} named by {len(wanted)} vtables at "
          f"slots {slots}", flush=True)
    where = OUT / "survey"
    where.mkdir(parents=True, exist_ok=True)

    def one(scene: str) -> str:
        frames = [f for f in scenes.SCENES[scene]["ram"] if f < scenes.SCENES[scene]["frames"] - 1]
        dump = where / f".dump-{scene}"
        try:
            dump_scene(scene, frames, seed, dump)
            found = {}
            for f in frames:
                image = Image(dump / f"ram-{f}-reference.bin")
                found[f] = {f"{v:08x}": objs for v, objs in objects_in(image, wanted).items()}
        except (subprocess.CalledProcessError, OSError) as e:
            return f"{scene}: the run failed ({e})"
        finally:
            for image in dump.glob("ram-*.bin"):
                image.unlink()
        (where / f"{scene}.json").write_text(json.dumps(found) + "\n")
        return f"{scene}: {sum(len(x) for x in found.values())} vtables with live objects over {len(frames)} frames"
    with cf.ThreadPoolExecutor(max(1, jobs)) as pool:
        for line in pool.map(one, [n for n in names if not (where / f"{n}.json").exists()]):
            print(line, flush=True)
    return 0


def plan(groups: list[str], slots: list[int], free_slots: list[int], prefix: str, most: int) -> int:
    """Check files <prefix>-<scene>-<frame>.txt from the survey: the scenes' moments taken greedily
    by how many functions they add, each function called once on a live object, no block called
    twice, a destructor that frees only on an object at the start of a block of a heap the game
    has a Heap for, with that heap made current around it."""
    targets = open_targets(groups)
    vts = vtable_slots(targets, slots)
    by_vtable: dict[tuple[int, int], list[tuple[str, int]]] = {}
    for key, vs in vts.items():
        for v, slot in vs:
            by_vtable.setdefault((v, slot), []).append(key)
    moments: dict[tuple[str, int], dict[tuple[str, int], list]] = {}  # (scene, frame) -> key -> candidates
    for path in sorted((OUT / "survey").glob("*.json")):
        for f, found in json.loads(path.read_text()).items():
            for (v, slot), keys in by_vtable.items():
                for o, start, _end, heap in found.get(f"{v:08x}", []):
                    if slot in free_slots and (o != start or heap == 0):
                        continue
                    for key in keys:
                        moments.setdefault((path.stem, int(f)), {}).setdefault(key, []).append((o, start, v, slot, heap))
    done: set[tuple[str, int]] = set()
    written = 0
    names: dict[str, int] = {}
    for old in CHECKS.glob(f"{prefix}-*.txt"):
        old.unlink()
    while True:
        best = max(moments, key=lambda m: (len(set(moments[m]) - done), m), default=None)
        if best is None or not set(moments[best]) - done:
            break
        scene, frame = best
        used_blocks: set[int] = set()
        lines: list[str] = []
        count = 0
        mine = []
        for key in sorted(set(moments[best]) - done):
            if count >= most:
                break
            for o, start, v, slot, heap in moments[best][key]:
                if start in used_blocks:
                    continue
                used_blocks.add(start)
                call = (f"vcall {frame + 1} {o:08x} {4 * slot:x} {o:08x} 0 0 0 {v:08x}  "
                        f"# {key[0]} {targets[key][1]} (slot {slot})")
                if slot in free_slots:
                    lines += [f"call {frame + 1} {HEAP_SET_CURRENT:08x} {heap:08x} 0 0 0 0 0  # Heap_SetCurrent(its heap)",
                              call, f"call {frame + 1} {HEAP_SET_CURRENT:08x} r2 0 0 0 0 0  # Heap_SetCurrent(as before)"]
                else:
                    lines.append(call)
                done.add(key)
                mine.append(key)
                count += 1
                break
        if not count:
            for key in set(moments[best]) - done:
                done.add(key)  # (every candidate's block is taken: none left here)
            continue
        sc = scenes.SCENES[scene]
        ram = [f for f in sc["ram"] if f < frame]
        text = [f"# {count} functions of {', '.join(sorted({targets[k][2] for k in mine}))}: each on a live object "
                f"of its class, through the object's vtable, at the end of frame {frame + 1} of {scene} "
                f"(tools/driven.py --plan)",
                f"scene {scene}", f"frames {frame + 10}", *([f"ram {','.join(map(str, ram))}"] if ram else []),
                f"arm {OS_SLEEP_THREAD:08x} {MAIN_FRAME_QUEUE:08x}  # OS_SleepThread(the main loop's queue)", *lines, "end"]
        name = f"{prefix}-{scene}-{frame + 1}"
        names[name] = names.get(name, 0) + 1
        if names[name] > 1:
            name += f"-{names[name]}"  # a moment picked again for the calls one check had no room for
        (CHECKS / f"{name}.txt").write_text("\n".join(text) + "\n", newline="\n")
        written += 1
        print(f"{name}: {count} functions", flush=True)
    print(f"{written} checks, {len(done)} of {len(targets)} functions")
    return 0


def scout(scene: str, frames: list[int], groups: list[str], slots: list[int], seed: pathlib.Path) -> int:
    targets = open_targets(groups)
    vts = vtable_slots(targets, slots)
    wanted = {v for vs in vts.values() for v, _ in vs}
    dump = OUT / "scout" / scene
    dump_scene(scene, frames, seed, dump)
    print(f"{len(targets)} open functions, {sum(1 for k in targets if k in vts)} named by a vtable")
    for f in frames:
        found = objects_in(Image(dump / f"ram-{f}-reference.bin"), wanted)
        have = 0
        print(f"frame {f}:")
        for key, vs in sorted(vts.items()):
            for v, slot in vs:
                objs = found.get(v, [])
                if objs:
                    have += 1
                    print(f"  {key[0]} {key[1]:08x} {targets[key][1]} (slot {slot} of {v:08x}): {len(objs)} objects")
                    for o, start, end, heap in objs[:4]:
                        place = f"block {start:08x}-{end:08x} of heap {heap:08x}" if heap else "a frame heap or .bss"
                        print(f"    vcall {f + 1} {o:08x} {4 * slot:x} {o:08x} 0 0 0 {v:08x}  # {targets[key][1]} ({place}"
                              f"{', its start' if o == start else ''})")
        print(f"  {have} of {len(targets)} have a live object")
    return 0


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("names", nargs="*")
    ap.add_argument("--seed", type=pathlib.Path, default=os.environ.get("ACWW_SCENE_SEED"))
    ap.add_argument("--list", action="store_true")
    ap.add_argument("--record", action="store_true")
    ap.add_argument("-j", type=int, default=2)
    ap.add_argument("--scout", metavar="SCENE")
    ap.add_argument("--frames")
    ap.add_argument("--group", action="append", default=[], help="a group of docs/scene-plan-groups.txt (repeatable)")
    ap.add_argument("--slots", default="0,1")
    ap.add_argument("--free-slots", default="1,17", help="the slots of destructors that free the object")
    ap.add_argument("--survey", nargs="*", metavar="SCENE", help="the scenes' live objects (no SCENE: every scene)")
    ap.add_argument("--plan", metavar="PREFIX", help="check files from the survey")
    ap.add_argument("--most", type=int, default=40, help="with --plan: the calls of a check at most")
    args = ap.parse_args()
    slots = [int(s) for s in args.slots.split(",")]
    if args.list:
        for n in checks():
            ch = read_check(n)
            calls = sum(1 for ln in ch["lines"] if ln.split()[0] in ("call", "vcall"))
            print(f"{n}: {ch['scene']}, {calls} calls; {' '.join(ch['intent'])}")
        return 0
    if args.record:
        return record()
    if args.plan:
        return plan(args.group, slots, [int(s) for s in args.free_slots.split(",")], args.plan, args.most)
    if args.seed is None:
        raise SystemExit("the seed save: --seed PATH or ACWW_SCENE_SEED")
    if args.survey is not None:
        return survey(args.survey or sorted(scenes.SCENES), args.group, slots, pathlib.Path(args.seed), args.j)
    if args.scout:
        return scout(args.scout, [int(f) for f in args.frames.split(",")], args.group, slots, pathlib.Path(args.seed))
    names = args.names or checks()
    unknown = [n for n in names if not (CHECKS / f"{n}.txt").exists()]
    if unknown:
        raise SystemExit(f"no such check: {', '.join(unknown)}")
    return run_all(names, pathlib.Path(args.seed), args.j)


if __name__ == "__main__":
    sys.exit(main())
