"""Build runtime/run.c and boot the game's ARM9 code in the interpreter (docs/runtime.md, M3).

    python tools/run.py                      # run until stuck or 200 M instructions
    python tools/run.py 50000000             # an instruction budget
    python tools/run.py 0 600                # no instruction budget, stop after 600 frames
    python tools/run.py 0 1300 --input runtime/recordings/title-start.txt --rtc "2005-11-23 12:00:00"
                        --png build/frames --frames 0-1300/50 --hash build/frames/hashes.txt
                                             # (one command) the recorded title run, saved and hashed

Options for the screens (docs/runtime.md, M3):
    --png DIR        save frames as DIR/frame-<n>.png (upper screen above the lower one)
    --png3d DIR      save the 3D engine's output alone as DIR/3d-<n>.png (transparent pixels
                     as a grey checkerboard), for the frames --frames lists
    --frames LIST    which frames to save: n, a-b or a-b/step, comma-separated (default all)
    --hash FILE|-    write "frame <n> <sha1 upper> <sha1 lower>" for every frame; the report
                     ends with one SHA-1 over the whole sequence, so two runs compare at a glance
    --input FILE     an input recording (format in runtime/input.h)
    --rtc "YYYY-MM-DD HH:MM:SS"  start the clock at a fixed moment and advance it with the
                     emulated time, so runs are identical (default: the host's clock)

Prints how far the boot gets: where it stopped, the registers the game touched, the BIOS
calls, the PXI traffic, the functions branched to most and the last branch targets with their
symbols. The ROM is extract/adm-kr.nds; the modules of build/adm-kr/rom are only compared
against memory after the crt0 has unpacked the program. Same compiler as tools/diffcheck.py.

Environment variables, for following a run on stderr:
    RUN_TRACE=card,pxi,irq print cartridge commands, PXI words, interrupt requests and DMAs
    RUN_TRACE=gx           print a line per rendered 3D frame (polygons, vertices, pixels drawn)
    RUN_CALLS=f1,f2,...    print each call of the named functions with r0-r3 and the frame
    RUN_BRANCHES=N         how many of the last branch targets the report lists (300)
"""

from __future__ import annotations

import argparse
import os
import pathlib
import subprocess
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import common as C  # noqa: E402
import diffcheck  # noqa: E402

OUT = C.BUILD / "runtime"
RUNTIME = C.ROOT / "runtime"
ROM = C.ROOT / "extract" / "adm-kr.nds"
SOURCES = ("arm.c", "memory.c", "io.c", "bios.c", "arm7.c", "boot.c", "gpu2d.c", "gpu3d.c", "frame.c", "input.c",
           "run.c")


def generate() -> tuple[pathlib.Path, pathlib.Path]:
    """The module manifest (as diffcheck writes it) and a flat symbol list for run.c."""
    OUT.mkdir(parents=True, exist_ok=True)
    mods = C.modules()
    manifest = OUT / "modules.txt"
    manifest.write_text(
        "".join(f"{m} {info['base']:08x} {C.ROM_DIR / (m + '.bin')}\n" for m, info in mods.items()),
        newline="\n")
    syms = C.SymbolTable(mods)
    rows = []
    for mod in C.RESIDENT:
        for s in syms.by_module.get(mod, []):
            if s.kind == "function" and s.size:
                rows.append(f"{s.address:08x} {s.size:x} {s.name}\n")
    # overlays live at overlapping addresses; only the resident modules are named
    table = OUT / "symbols.txt"
    table.write_text("".join(sorted(rows)), newline="\n")
    return manifest, table


def build() -> pathlib.Path:
    exe = OUT / ("run.exe" if os.name == "nt" else "run")
    flags = ["-std=c11", "-O2", "-Wall", "-Wextra", "-fwrapv", "-fno-strict-aliasing", "-D_CRT_SECURE_NO_WARNINGS",
             "-D_CRT_NONSTDC_NO_WARNINGS", f"-I{RUNTIME}"]
    srcs = [str(RUNTIME / n) for n in SOURCES]
    p = subprocess.run([*diffcheck.compiler(), *flags, *srcs, "-o", str(exe)], capture_output=True, text=True)
    if p.returncode != 0:
        raise SystemExit(p.stdout + p.stderr)
    if p.stderr.strip():
        print(p.stderr, file=sys.stderr)
    return exe


def main() -> None:
    ap = argparse.ArgumentParser(description="Boot the game in the interpreter.")
    ap.add_argument("max_instructions", nargs="?", help="instruction budget (0: none; default 200 M)")
    ap.add_argument("max_frames", nargs="?", help="stop after this many frames")
    ap.add_argument("--png", metavar="DIR", help="save frames as PNGs in DIR")
    ap.add_argument("--png3d", metavar="DIR", help="save the 3D layer alone as PNGs in DIR")
    ap.add_argument("--frames", metavar="LIST", help="frames to save: n, a-b, a-b/step, comma-separated")
    ap.add_argument("--hash", metavar="FILE", help="per-frame SHA-1s to FILE, or - for stdout")
    ap.add_argument("--input", metavar="FILE", help="input recording")
    ap.add_argument("--rtc", metavar="TIME", help='pin the clock: "YYYY-MM-DD HH:MM:SS"')
    args = ap.parse_args()
    if not ROM.exists():
        raise SystemExit(f"no ROM at {ROM}")
    manifest, table = generate()
    exe = build()
    env = dict(os.environ)
    if args.png:
        pathlib.Path(args.png).mkdir(parents=True, exist_ok=True)
        env["RUN_PNG"] = str(pathlib.Path(args.png).resolve())
    if args.png3d:
        pathlib.Path(args.png3d).mkdir(parents=True, exist_ok=True)
        env["RUN_DUMP3D"] = str(pathlib.Path(args.png3d).resolve())
    if args.frames:
        env["RUN_PNG_FRAMES"] = args.frames
    if args.hash:
        if args.hash != "-":
            pathlib.Path(args.hash).resolve().parent.mkdir(parents=True, exist_ok=True)
        env["RUN_HASH"] = args.hash if args.hash == "-" else str(pathlib.Path(args.hash).resolve())
    if args.input:
        env["RUN_INPUT"] = str(pathlib.Path(args.input).resolve())
    if args.rtc:
        env["RUN_RTC"] = args.rtc
    budget = [a for a in (args.max_instructions, args.max_frames) if a is not None]
    p = subprocess.run([str(exe), str(ROM), str(manifest), str(table), *budget], cwd=C.ROOT, env=env)
    sys.exit(p.returncode)


if __name__ == "__main__":
    main()
