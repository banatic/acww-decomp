"""tools/run.py's Reference cache: which runtime sources its key holds, that the files it leaves
out without their variable are entered only where that variable is checked, and that an entry
gives back exactly what it kept (and tells a run that differs from it)."""
from __future__ import annotations

import array
import json
import os
import pathlib
import random
import re
import shutil
import sys
import tempfile

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import common as C  # noqa: E402
import run  # noqa: E402

RUNTIME = run.RUNTIME
# The flags that say a gated file may be entered, by variable: a call into one of its files is
# on a line that tests one of them, or within the three lines after one.
GUARDS = {"RUN_WIRELESS": ("arm7.wireless", 'env_on("RUN_WIRELESS")', "arm7_wifi()"),
          "RUN_SEQUENCER": ("arm7.sequencer", 'env_on("RUN_SEQUENCER")')}
# where each flag is set: once, from its variable
SET_FROM = {"arm7.wireless": 'env_on("RUN_WIRELESS")', "arm7.wifi": "arm7.wireless",
            "arm7.sequencer": 'env_on("RUN_SEQUENCER")'}
FUNCTION = re.compile(r"^(?!static\b|typedef\b|enum\b|struct\b|#)[A-Za-z][^;=]*?\b(\w+)\s*\(", re.M)


def check_entries() -> list[str]:
    """Every function of a gated file has its file's prefix (none takes the place of another of the
    same name, which the Native link allows), and the other sources reach them only under a guard."""
    bad = []
    gated = {name: gate for name, gate in run.FEATURE_SOURCES.items()}
    names: dict[str, str] = {}
    for source, gate in gated.items():
        prefix = source[:-2] + "_"
        for name in FUNCTION.findall((RUNTIME / source).read_text()):
            if not name.startswith(prefix):
                bad.append(f"{source}: {name} is external without the prefix {prefix}")
            names[name] = gate
    if not names:
        return ["no functions found in the gated files"]
    pattern = re.compile(r"\b(" + "|".join(sorted(names)) + r")\b")
    for path in sorted(RUNTIME.glob("*.c")):
        if path.name in gated:
            continue
        lines = path.read_text().splitlines()
        for i, line in enumerate(lines):
            for m in pattern.finditer(line):
                window = "\n".join(lines[max(0, i - 3):i + 1])
                if not any(g in window for g in GUARDS[names[m.group(1)]]):
                    bad.append(f"{path.name}:{i + 1}: {m.group(1)} without a check of {names[m.group(1)]}")
    text = (RUNTIME / "arm7.c").read_text()
    for flag, source in SET_FROM.items():
        sets = re.findall(rf"^\s*{re.escape(flag)} = (.*);$", text, re.M)
        if len(sets) != 1 or not sets[0].startswith(source + " && "):
            bad.append(f"arm7.c: {flag} is set other than once from {source}: {sets}")
    return bad


def check_scope() -> list[str]:
    """The key's sources for a run of the program as tools/run.py builds it, with and without the
    variables."""
    bad = []
    inputs = run.program_inputs(["cc", "-O2", *(str(RUNTIME / n) for n in run.SOURCES), str(RUNTIME / "native_rt.c"),
                                 "@objects.txt", "x.o", "-Wl,/MAP:a.map", "-o", "a.exe"],
                                [RUNTIME / n for n in run.SOURCES] + [RUNTIME / "native_rt.c"])
    if inputs["command"] != ["cc", "-O2"]:
        bad.append(f"command kept {inputs['command']}")
    for env, wanted, unwanted in (
            ({}, {"arm7.c", "run.c", "native_run.c", "wm.h", "wifi.h", "sequencer.h"}, {"wm.c", "wifi.c", "sequencer.c"}),
            ({"RUN_WIRELESS": "1"}, {"wm.c", "wifi.c"}, {"sequencer.c"}),
            ({"RUN_SEQUENCER": "1"}, {"sequencer.c"}, {"wm.c", "wifi.c"})):
        names = {p.name for p in run.reference_sources(inputs, env)}
        unwanted |= {"diffcheck.c", "nativecheck.c", "play.c", "native_none.c", "clean_ran.c"}
        if not wanted <= names or names & unwanted:
            bad.append(f"{env}: sources {sorted(names)}")
    return bad


def check_entry() -> list[str]:
    """A made-up run kept and put back, a record that spans chunks, and a fresh run that differs."""
    bad = []
    with tempfile.TemporaryDirectory() as tmp:
        tmp = pathlib.Path(tmp)
        saved = C.CACHE_DIR, run.CHUNK_RECORDS, os.environ.pop("ACWW_NO_REFERENCE_CACHE", None)
        C.CACHE_DIR, run.CHUNK_RECORDS = tmp / "cache", 1000
        try:
            out, ram = tmp / "out", tmp / "out" / "ram"
            ram.mkdir(parents=True)
            rng = random.Random(7)
            steps = 0
            words = array.array("I")
            for i in range(2500):
                steps += rng.randrange(1 << 20) if i % 9 else -rng.randrange(1 << 20)  # (not always rising)
                steps &= (1 << 64) - 1
                words.extend([i % 3, i % 7, 0x02000000 + i, steps & 0xFFFFFFFF, steps >> 32,
                              *(rng.randrange(1 << 32) for _ in range(5))])
            files = {"crossings.bin": words.tobytes(), "reference.log": b"frames: sequence sha1 0\nX: C:\\a\\b\n",
                     "reference-hashes.txt": b"frame 0 a b\n", "functions-seen.txt": b"main 02000000 f\n",
                     "ram/ram-1-reference.bin": bytes(rng.randrange(256) for _ in range(5000)),
                     "ram/ram-2-reference.bin": bytes(4000)}
            for name, data in files.items():
                (out / name).write_bytes(data)
            trace = out / "crossings.bin"
            run.keep_reference("ab" * 20, out, ram, trace)
            if run.reference_differs("ab" * 20, out, ram, trace):
                bad.append("a run differs from its own entry")
            shutil.rmtree(out)
            ram.mkdir(parents=True)
            if not run.reference_cached("ab" * 20, out, ram, trace):
                bad.append("the entry did not come back")
            for name, data in files.items():
                if (out / name).read_bytes() != data:
                    bad.append(f"{name} came back changed")
            (out / "reference.log").write_bytes(b"frames: sequence sha1 0\nX: D:\\c\n")  # only a path: the same
            (out / "ram" / "ram-2-reference.bin").write_bytes(bytes(3999) + b"\1")
            if run.reference_differs("ab" * 20, out, ram, trace) != ["ram/ram-2-reference.bin"]:
                bad.append(f"a changed image: {run.reference_differs('ab' * 20, out, ram, trace)}")
            index = json.loads((run.reference_entry("ab" * 20) / "index.json").read_text())
            index[0][2] = "0" * 40
            (run.reference_entry("ab" * 20) / "index.json").write_text(json.dumps(index))
            if run.reference_cached("ab" * 20, out, ram, trace):
                bad.append("an entry whose file does not match its SHA-1 was used")
        finally:
            C.CACHE_DIR, run.CHUNK_RECORDS = saved[0], saved[1]
            if saved[2] is not None:
                os.environ["ACWW_NO_REFERENCE_CACHE"] = saved[2]
    return bad


def main() -> int:
    bad = check_entries() + check_scope() + check_entry()
    for line in bad:
        print(f"FAIL: {line}")
    print("the Reference cache's key and entries: " + ("FAIL" if bad else "ok"))
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
