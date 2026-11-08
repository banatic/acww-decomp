"""Build the playable program (runtime/play.c, docs/play.md) and start it.

    python tools/play.py                         # build, then play (save in %APPDATA%\\acwwdecomp\\acww.sav)
    python tools/play.py my-town.sav             # play with this save file (read, and written when the game saves)
    python tools/play.py --form native           # Native code without the Clean versions
    python tools/play.py --form reference        # every function as the ROM's code (the interpreter)
    python tools/play.py --build-only            # only build; prints the program's path
    python tools/play.py --localize es --european GAME.nds  # experimental resources (docs/localized-clean.md)

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
import os
import pathlib
import shutil
import subprocess
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import run  # noqa: E402

FORMS = {"clean": "acww-play", "native": "acww-play-native", "reference": "acww-play-reference"}


def build(form: str, localized_rom: pathlib.Path | None = None, language: str | None = None) -> pathlib.Path:
    """The program for `form` and its .cfg; returns the program's path."""
    if not run.WINDOWS:
        raise SystemExit("the play front end is written for Windows (runtime/play.c)")
    if not run.ROM.exists():
        raise SystemExit(f"no ROM at {run.ROM} (see INSTALL.md)")
    name = FORMS[form]
    if language:
        name += "-" + language
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
    config = (f"form={form.capitalize()}{'/' + language if language else ''}\n"
              f"rom={(localized_rom or run.ROM).resolve()}\nmodules={manifest.resolve()}\n"
              f"symbols={table.resolve()}\npolicy={policy}\n")
    if localized_rom:
        save_dir = pathlib.Path(os.environ.get("APPDATA", str(run.C.BUILD))) / "acwwdecomp" / "localized-clean"
        save_dir.mkdir(parents=True, exist_ok=True)
        config += f"save={save_dir / 'acww.sav'}\n"
    cfg.write_text(config, newline="\n")
    return exe


def main() -> None:
    ap = argparse.ArgumentParser(description="Build the playable program and start it.", add_help=False)
    ap.add_argument("--form", choices=sorted(FORMS), default="clean",
                    help="clean (default: Native with every Clean function), native, or reference")
    ap.add_argument("--build-only", action="store_true", help="build, print the program's path, do not start it")
    ap.add_argument("-h", "--help", action="store_true")
    ap.add_argument("--localize", choices=("en", "fr", "de", "es", "it"),
                    help="experimental European resources for the Korean runtime (docs/localized-clean.md)")
    ap.add_argument("--european", type=pathlib.Path, help="your European ADMP revision 0 .nds (with --localize)")
    ap.add_argument("--latin-keyboard", action="store_true", help="Latin accent keys (requires --localize)")
    args, rest = ap.parse_known_args()
    if args.help:
        print(__doc__)
        return
    localized_rom = None
    if args.localize:
        if args.european is None:
            ap.error("--localize requires --european PATH/TO/GAME.nds")
        import localize_clean
        try:
            localized_rom, report = localize_clean.prepare(run.ROM, args.european, args.localize, args.latin_keyboard)
        except (ValueError, OSError, KeyError) as exc:
            ap.error(str(exc))
        print(f"localized resources: {report['replaced_files']} replaced, "
              f"{len(report['fallback_files'])} original files kept; see {localized_rom.parent / 'report.json'}",
              flush=True)
    elif args.european is not None or args.latin_keyboard:
        ap.error("--european and --latin-keyboard require --localize")
    exe = build(args.form, localized_rom, args.localize)
    if args.build_only:
        print(exe)
        return
    sys.exit(subprocess.call([str(exe), *rest], cwd=run.C.ROOT))


if __name__ == "__main__":
    main()
