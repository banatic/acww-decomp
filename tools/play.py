"""Build the playable program (runtime/play.c, docs/play.md) and start it.

    python tools/play.py                         # build, then play (save in %APPDATA%\\acwwdecomp\\acww.sav)
    python tools/play.py my-town.sav             # play with this save file (read, and written when the game saves)
    python tools/play.py --form native           # Native code without the Clean versions
    python tools/play.py --form reference        # every function as the ROM's code (the interpreter)
    python tools/play.py --build-only            # only build; prints the program's path

The program is the runtime of tools/run.py (the same sources, the same Native and Clean objects:
run `python tools/native.py` first for the Native and Clean forms) with a window in front. It is
written to the runtime's build directory (ACWW_RUNTIME_OUT, else build/runtime) as
acww-play.exe (Clean), acww-play-native.exe or acww-play-reference.exe, with a .cfg beside it
naming the ROM, the module list, the symbols and the Native policy it runs with; started without
this script it reads that file. Every other option is the program's own (`--help` lists them):
--read-only, --reference, --rtc, --input, --scale, --frames.

Windows only for now.
"""

from __future__ import annotations

import argparse
import pathlib
import shutil
import subprocess
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import run  # noqa: E402

FORMS = {"clean": "acww-play", "native": "acww-play-native", "reference": "acww-play-reference"}


def build(form: str) -> pathlib.Path:
    """The program for `form` and its .cfg; returns the program's path."""
    if not run.WINDOWS:
        raise SystemExit("the play front end is written for Windows (runtime/play.c)")
    if not run.ROM.exists():
        raise SystemExit(f"no ROM at {run.ROM} (see INSTALL.md)")
    name = FORMS[form]
    manifest, table = run.generate()
    policy = ""
    if form == "reference":
        exe = run.build(native=False, play=name)
    else:
        if not (run.NATIVE / "natives.s").exists():
            raise SystemExit("run `python tools/native.py` first (or use --form reference)")
        clean = "all" if form == "clean" else None
        written = run.write_policy("all", clean)
        exe = run.build(native=True, clean=clean, play=name)
        kept = run.OUT / f"{name}-policy.txt"
        shutil.copyfile(written, kept)
        policy = str(kept.resolve())
    cfg = exe.with_suffix(".cfg")
    cfg.write_text(f"form={form.capitalize()}\nrom={run.ROM.resolve()}\nmodules={manifest.resolve()}\n"
                   f"symbols={table.resolve()}\npolicy={policy}\n", newline="\n")
    return exe


def main() -> None:
    ap = argparse.ArgumentParser(description="Build the playable program and start it.", add_help=False)
    ap.add_argument("--form", choices=sorted(FORMS), default="clean",
                    help="clean (default: Native with every Clean function), native, or reference")
    ap.add_argument("--build-only", action="store_true", help="build, print the program's path, do not start it")
    ap.add_argument("-h", "--help", action="store_true")
    args, rest = ap.parse_known_args()
    if args.help:
        print(__doc__)
        return
    exe = build(args.form)
    if args.build_only:
        print(exe)
        return
    sys.exit(subprocess.call([str(exe), *rest], cwd=run.C.ROOT))


if __name__ == "__main__":
    main()
