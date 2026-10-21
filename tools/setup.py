"""From your own copy of the game to a checked runtime and a playable program, in one command.

    python tools/setup.py PATH/TO/GAME.nds          # check the ROM, extract, build, self-test
    python tools/setup.py PATH/TO/GAME.nds --play   # ... then start the game in a window
    python tools/setup.py --check                   # only the self-test, on the ROM already set up
    python tools/setup.py ... --quick               # the self-test's short part only
    python tools/setup.py ... --matching            # also compile every source with the original
                                                    # compiler and link (needs mwccarm, INSTALL.md)

Steps, each saying what is wrong and how to fix it when it fails:

1. The ROM: its header must name the Korean release (ADMK, revision 0) and its SHA-1 must be
   the one in adm-kr.sha1. A dump trimmed to the ROM's used size is padded back with 0xff as
   the cartridge reads; another region or revision, or a bad dump, is refused with what it is.
   The ROM is copied to extract/adm-kr.nds (never modified in place) and split into the ARM9
   modules (tools/extract.py).
2. The tools: Python 3.11+, and a C compiler for 32-bit x86 (clang with the MSVC libraries on
   Windows, gcc -m32 elsewhere; tools/diffcheck.py's compiler()).
3. The build: the sources compiled for the PC (tools/native.py) and the window program
   (tools/play.py --build-only).
4. The self-test: the title recording (runtime/recordings/title-start.txt) in the interpreter,
   with the matching sources and with the Clean rewrites, each giving the expected frames; then
   (without --quick) the new-game recording the same way. This checks the runtime on this
   machine: the same frames as on the project's machines, bit for bit.

Nothing of the game is in the repository; everything taken from the ROM stays under extract/
and build/.
"""
from __future__ import annotations

import argparse
import hashlib
import os
import pathlib
import shutil
import struct
import subprocess
import sys
import time

ROOT = pathlib.Path(__file__).resolve().parents[1]
EXTRACT = ROOT / "extract"
TARGET = EXTRACT / "adm-kr.nds"
WANT_SHA1 = (ROOT / "adm-kr.sha1").read_text(encoding="utf-8").split()[0].lower()
FULL_SIZE = 32 << 20           # the cartridge: 256 Mbit
USED_SIZE = 0x1F533C4          # the header's used size (0x80)
TRIMMED_SHA1 = "f987baf1db78b9b8c92a98877c62df71f9d049d3"

# Animal Crossing: Wild World releases (game code -> region), to say what a wrong ROM is.
RELEASES = {"ADME": "North America", "ADMJ": "Japan", "ADMP": "Europe", "ADMK": "Korea",
            "ADMU": "Australia", "ADMC": "China (iQue)"}

RTC = "2005-11-23 12:00:00"
RECORDINGS = [("title-start", 1300), ("new-game", 13760)]


def fail(what: str, fix: str) -> None:
    sys.exit(f"setup: {what}\n  -> {fix}")


def step(text: str) -> None:
    print(f"== {text}", flush=True)


def header_crc(data: bytes) -> int:
    """The CRC-16 (polynomial 0xa001, start 0xffff) the header keeps at 0x15e over 0x000-0x15d."""
    crc = 0xFFFF
    for b in data[:0x15E]:
        crc ^= b
        for _ in range(8):
            crc = (crc >> 1) ^ 0xA001 if crc & 1 else crc >> 1
    return crc


def check_rom(path: pathlib.Path) -> bytes:
    if not path.is_file():
        fail(f"{path}: no such file", "give the path of your .nds dump")
    data = path.read_bytes()
    if len(data) < 0x200:
        fail(f"{path.name}: {len(data)} bytes, not a DS ROM", "dump the cartridge again")
    if header_crc(data) != struct.unpack_from("<H", data, 0x15E)[0]:
        fail(f"{path.name}: the header's checksum is wrong: not a DS ROM, or a damaged dump",
             "dump the cartridge again")
    title = data[0:12].rstrip(b"\0").decode("ascii", "replace")
    code = data[12:16].decode("ascii", "replace")
    revision = data[0x1E]
    if code[:3] != "ADM":
        fail(f"{path.name}: the header names '{title}' ({code}), not Animal Crossing: Wild World",
             "use a dump of Animal Crossing: Wild World (Korea, ADMK)")
    if code != "ADMK":
        fail(f"{path.name}: the {RELEASES.get(code, code)} release ({code}); this project is the Korean one (ADMK)",
             "use a dump of the Korean cartridge")
    if revision != 0:
        fail(f"{path.name}: revision {revision}; the project's ROM is revision 0", "use a revision 0 dump")
    sha1 = hashlib.sha1(data).hexdigest()
    if sha1 == WANT_SHA1:
        return data
    if len(data) == USED_SIZE and sha1 == TRIMMED_SHA1:
        print(f"setup: {path.name} is trimmed to the used size; padding it back with 0xff")
        return data + b"\xff" * (FULL_SIZE - len(data))
    if len(data) > FULL_SIZE or (len(data) >= USED_SIZE and hashlib.sha1(data[:USED_SIZE]).hexdigest() == TRIMMED_SHA1):
        print(f"setup: {path.name}'s padding differs from the cartridge's; keeping the used part, padded with 0xff")
        return data[:USED_SIZE] + b"\xff" * (FULL_SIZE - USED_SIZE)
    fail(f"{path.name}: SHA-1 {sha1}, expected {WANT_SHA1} (header ADMK, revision 0: a bad or modified dump)",
         "dump the cartridge again; patched or translated ROMs are not supported")
    return b""


def run(cmd: list[str], log: pathlib.Path, env: dict | None = None) -> tuple[int, str]:
    log.parent.mkdir(parents=True, exist_ok=True)
    with open(log, "w", encoding="utf-8", errors="replace") as out:
        status = subprocess.run(cmd, cwd=ROOT, stdout=out, stderr=subprocess.STDOUT, env=env or os.environ).returncode
    text = log.read_text(encoding="utf-8", errors="replace")
    return status, text


def check_tools() -> None:
    if sys.version_info < (3, 11):
        fail(f"Python {sys.version.split()[0]}", "install Python 3.11 or newer")
    sys.path.insert(0, str(ROOT / "tools"))
    import diffcheck  # noqa: PLC0415
    cc = diffcheck.compiler()
    if shutil.which(cc[0]) is None and not pathlib.Path(cc[0]).exists():
        hint = ("install LLVM (winget install LLVM.LLVM) and the Visual Studio Build Tools' C++ workload "
                "(its libraries), or set CC" if os.name == "nt" else "install gcc with 32-bit support "
                "(gcc-multilib), or set CC")
        fail(f"no C compiler for 32-bit x86 ({cc[0]})", hint)
    probe = ROOT / "build" / "setup" / "probe.c"
    probe.parent.mkdir(parents=True, exist_ok=True)
    probe.write_text("#include <stdio.h>\nint main(void) { puts(\"ok\"); return 0; }\n")
    exe = probe.with_suffix(".exe" if os.name == "nt" else "")
    status, text = run([*cc, str(probe), "-o", str(exe)], probe.with_suffix(".log"))
    if status != 0:
        fail(f"{cc[0]} cannot build a 32-bit program:\n{text[-1500:]}",
             "on Windows install the Visual Studio Build Tools (C++ workload) for the libraries clang links with; "
             "elsewhere gcc-multilib")
    print(f"setup: compiler ok ({' '.join(cc)})")


def self_test(quick: bool) -> bool:
    logs = ROOT / "build" / "setup"
    ok = True
    for name, frames in RECORDINGS[:1] if quick else RECORDINGS:
        rec = f"runtime/recordings/{name}"
        for form, extra in (("interpreter", []), ("matching sources", ["--native=all"]),
                            ("Clean rewrites", ["--native=all", "--clean"])):
            start = time.time()
            cmd = [sys.executable, "tools/run.py", "0", str(frames), "--input", f"{rec}.txt", "--rtc", RTC,
                   "--expect", f"{rec}.sha1", *extra]
            if not extra:  # the interpreter alone: compare the frame sequence itself
                cmd = [sys.executable, "tools/run.py", "0", str(frames), "--input", f"{rec}.txt", "--rtc", RTC,
                       "--hash", str(logs / f"{name}-hashes.txt")]
            status, text = run(cmd, logs / f"{name}-{form.split()[0]}.log")
            if not extra and status == 0:
                want = (ROOT / f"{rec}.sha1").read_text().split()[0]
                status = 0 if want in text else 1
            good = status == 0
            ok &= good
            print(f"{'ok  ' if good else 'FAIL'} {name}, {form} ({time.time() - start:.0f} s)"
                  + ("" if good else f": see {logs / f'{name}-{form.split()[0]}.log'}"), flush=True)
    return ok


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("rom", nargs="?", type=pathlib.Path, help="your dump of the game (.nds)")
    ap.add_argument("--check", action="store_true", help="only the self-test")
    ap.add_argument("--quick", action="store_true", help="the self-test's title recording only")
    ap.add_argument("--matching", action="store_true", help="also verify and link with mwccarm (INSTALL.md)")
    ap.add_argument("--play", action="store_true", help="start the game when done (Windows)")
    args = ap.parse_args()

    if not args.check:
        if args.rom is None:
            if not TARGET.exists():
                fail("no ROM given", "python tools/setup.py PATH/TO/GAME.nds")
            args.rom = TARGET
        step("1/4 the ROM")
        data = check_rom(args.rom)
        EXTRACT.mkdir(exist_ok=True)
        if args.rom.resolve() != TARGET.resolve() or TARGET.read_bytes() != data:
            TARGET.write_bytes(data)
        status, text = run([sys.executable, "tools/extract.py"], ROOT / "build" / "setup" / "extract.log")
        if status != 0:
            fail(f"tools/extract.py failed:\n{text[-1500:]}", "report it with build/setup/extract.log")
        print("setup: " + text.strip().splitlines()[-1])
        step("2/4 the tools")
        check_tools()
        step("3/4 the build (several minutes the first time)")
        for name, cmd in (("native", [sys.executable, "tools/native.py"]),
                          ("play", [sys.executable, "tools/play.py", "--build-only"])):
            if name == "play" and os.name != "nt":
                continue
            status, text = run(cmd, ROOT / "build" / "setup" / f"{name}.log")
            if status != 0:
                fail(f"tools/{name}.py failed:\n{text[-1500:]}", f"see build/setup/{name}.log")
            print(f"setup: {text.strip().splitlines()[-1] if text.strip() else name + ' ok'}")
    elif not TARGET.exists():
        fail("no ROM set up yet", "python tools/setup.py PATH/TO/GAME.nds")
    step("4/4 the self-test")
    if not self_test(args.quick):
        print("setup: the runtime does not give the project's frames on this machine; please report it with "
              "build/setup/*.log")
        return 1
    if args.matching:
        step("matching: every source with the original compiler, then the link")
        for name in ("verify", "link"):
            status, text = run([sys.executable, f"tools/{name}.py"], ROOT / "build" / "setup" / f"{name}.log")
            print(f"{'ok  ' if status == 0 else 'FAIL'} tools/{name}.py: {text.strip().splitlines()[-1] if text.strip() else ''}")
            if status != 0:
                return 1
    print("setup: done. Play with: python tools/play.py [SAVE.sav]  (docs/play.md)")
    if args.play:
        os.execv(sys.executable, [sys.executable, str(ROOT / "tools" / "play.py")])
    return 0


if __name__ == "__main__":
    sys.exit(main())
