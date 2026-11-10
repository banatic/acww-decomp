"""tools/run.py's Reference cache: which runtime sources its key holds, that the files it leaves
out without their variable are entered only where that variable is checked, that an entry
gives back exactly what it kept (and tells a run that differs from it), that the key's view of
each table holds everything but the names, and that an entry made under other names comes back
with the names asked for."""
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

NATIVES = """\t.data
\t.globl _native_module_names
_native_module_names:
\t.long native_module_name_0
\t.long native_module_name_1
\t.globl _native_module_count
_native_module_count:
\t.long 2
native_module_name_0:
\t.asciz "main"
native_module_name_1:
\t.asciz "ov001"
\t.p2align 2
\t.globl _native_functions
_native_functions:
\t.long 0x02000101, 0x10, _native_alpha, 0x00000015
\t.long 0x02000200, 0x20, _native_beta, 0x00010025
\t.globl _native_function_count
_native_function_count:
\t.long 2
\t.text
\t.p2align 4
\t.globl _native_call_gamma
_native_call_gamma:
\tjmp _native_alpha
\t.data
\t.globl _native_bodies
_native_bodies:
\t.long 0, 0
\t.globl _native_body_count
_native_body_count:
\t.long 0
\t.globl _native_private
_native_private:
\t.long 0x02000100, 0x02100000, 0x02100010
\t.globl _native_private_count
_native_private_count:
\t.long 1
"""
ROWS = ("\t.long 0x02000101, 0x10, _native_alpha, 0x00000015\n", "\t.long 0x02000200, 0x20, _native_beta, 0x00010025\n")
CLEAN_TABLE = """#include "native_table.h"

extern const DiffTest diff_test_alpha;
uint32_t native_body_clean_0(uint32_t a0)
{
    return diff_test_alpha.run_clean(args);
}
extern void native_clean_0(void);

extern void Beta_Run(void);
const NativeFunction clean_functions[] = {
    {0x02000101u, 0x10u, (const void *) native_clean_0, (uint32_t) NATIVE_RET_32 | 4u << 4 | (uint32_t) 0 << 16},
    {0x02000200u, 0x20u, (const void *) Beta_Run, 0x00010025u},
};
const uint32_t clean_function_count = 2;
"""
POLICY = ("02000101 main 10 N alpha 1 1 -1 -1 -1 0 0\n"
          "02000200 ov001 20 N beta 2 2 -1 -1 -1 0 0\n"
          "02000300 main 8 H _dadd -1 -1 -1 -1 -1 0 0\n")


def check_facts() -> list[str]:
    """The key's views: the same for other names, comments and orders that mean the same, and
    different for anything a Reference run reads."""
    bad = []

    def same(what: str, view, a: str, b: str, want: bool = True) -> None:
        if (view(a) == view(b)) != want:
            bad.append(f"{what}: {'differ' if want else 'the same'}")
    code = 'int a; /* one */\n// two\nint b = \'"\'; char *s = "/* not one */ // nor this";\n#define M(x) \\\n    (x)\n\nint c;\n'
    strip = run.strip_comments
    same("a comment reworded", strip, code, code.replace("/* one */", "/* another */").replace("// two", "// 2"))
    same("a comment line added", strip, code, code.replace("int c;", "/* new\n   lines */\nint c;"))
    same("a comment that runs on", strip, code, code.replace("// two\n", "// two \\\nthree\n"))
    same("code changed", strip, code, code.replace("int c", "int d"), False)
    same("a string changed", strip, code, code.replace("not one", "not two"), False)
    if "\\\n\nint c;" not in strip("#define M(x) (x) \\\n\nint c;\n"):
        bad.append("the empty line that ends a continued macro was taken out")
    if '"/* not one */ // nor this"' not in strip(code) or "one */\n" in strip(code):
        bad.append(f"comments stripped wrong: {strip(code)!r}")
    numbered = code + "int line = __LINE__;\n"
    same("a line added before __LINE__", strip, numbered, numbered.replace("int c;", "/* new */\n\nint c;"), False)
    same("a comment reworded before __LINE__", strip, numbered, numbered.replace("/* one */", "/* another */"))
    same("a trigraph", strip, code + "// ??/\n", code + "// other ??/\n", False)

    facts = run.natives_facts
    if facts(NATIVES) == NATIVES.encode():
        bad.append("natives.s was not read")
    same("natives.s renamed", facts, NATIVES, NATIVES.replace("alpha", "first").replace("beta", "second"))
    same("natives.s rows in another order", facts, NATIVES, NATIVES.replace(ROWS[0] + ROWS[1], ROWS[1] + ROWS[0]))
    same("natives.s stubs", facts, NATIVES, NATIVES.replace("jmp _native_alpha", "jmp _native_beta"))
    same("natives.s info", facts, NATIVES, NATIVES.replace("0x00000015", "0x00000025"), False)
    same("natives.s size", facts, NATIVES, NATIVES.replace("0x10, _native", "0x14, _native"), False)
    same("natives.s module", facts, NATIVES, NATIVES.replace('"ov001"', '"ov002"'), False)
    same("natives.s private", facts, NATIVES, NATIVES.replace("0x02100010", "0x02100020"), False)
    twice = NATIVES.replace(ROWS[1], ROWS[1].replace("0x02000200", "0x02000100").replace("0x00010025", "0x00000025"))
    swapped = twice.replace(ROWS[0], "").replace("\t.globl _native_function_count", ROWS[0] + "\t.globl _native_function_count")
    same("natives.s two rows of one function swapped", facts, twice, swapped, False)
    if facts(NATIVES.replace("\t.long 2\n\t.text", "\t.long 3\n\t.text")) != NATIVES.replace(
            "\t.long 2\n\t.text", "\t.long 3\n\t.text").encode():
        bad.append("natives.s with a wrong count was not taken whole")

    absolute = "\t.globl _a\n\t.set _a, 0x02000000\n\t.globl _b\n\t.set _b, 0x02000010\n"
    same("absolute.s renamed", run.absolute_facts, absolute, absolute.replace("_a", "_z"))
    same("absolute.s moved", run.absolute_facts, absolute, absolute.replace("0x02000010", "0x02000014"), False)
    if run.absolute_facts(absolute + "\t.long 1\n") != (absolute + "\t.long 1\n").encode():
        bad.append("absolute.s with another line was not taken whole")

    facts = run.clean_table_facts
    if facts(CLEAN_TABLE) == CLEAN_TABLE.encode():
        bad.append("clean_table.c was not read")
    same("clean_table.c renamed", facts, CLEAN_TABLE, CLEAN_TABLE.replace("Beta_Run", "Beta_Start").replace("alpha", "first"))
    same("clean_table.c info", facts, CLEAN_TABLE, CLEAN_TABLE.replace("0x00010025u", "0x00010825u"), False)
    same("clean_table.c result", facts, CLEAN_TABLE, CLEAN_TABLE.replace("NATIVE_RET_32", "NATIVE_RET_U8"), False)
    same("clean_table.c a row less", facts, CLEAN_TABLE, CLEAN_TABLE.replace(
        "    {0x02000200u, 0x20u, (const void *) Beta_Run, 0x00010025u},\n", "").replace("count = 2", "count = 1"), False)
    odd = CLEAN_TABLE.replace("(const void *) Beta_Run, 0x00010025u", "(const void *) Beta_Run, beta_info")
    if facts(odd) != odd.encode():
        bad.append("clean_table.c with a row it cannot read was not taken whole")

    same("the policy renamed", run.policy_facts, POLICY, POLICY.replace("alpha", "first"))
    same("the policy's helper renamed", run.policy_facts, POLICY, POLICY.replace("_dadd", "_dsub"), False)
    same("the policy's status", run.policy_facts, POLICY, POLICY.replace("N beta", "R beta"), False)
    same("the policy's words", run.policy_facts, POLICY, POLICY.replace("beta 2 2", "beta 2 3"), False)
    symbols = "02000100 10 alpha\n02000200 20 beta\n"
    same("the symbols renamed", run.symbols_facts, symbols, symbols.replace("alpha", "first"))
    same("the symbols' sizes", run.symbols_facts, symbols, symbols.replace(" 10 ", " 14 "), False)
    calls = "arm 02114c6c 021cfb98  # the main loop\nvcall 8001 023a39cc 8 023a39cc 0 0 0 02255ea4   # Swimmer_Destruct\nend\n"
    same("a driven check's comments", run.driven_facts, calls, calls.replace("Swimmer_Destruct", "Fish_Destruct").replace("end", "\nend"))
    same("a driven check's call", run.driven_facts, calls, calls.replace("8001", "8002"), False)
    return bad


def check_names() -> list[str]:
    """An entry made under some names, put back under others."""
    bad = []
    with tempfile.TemporaryDirectory() as tmp:
        tmp = pathlib.Path(tmp)
        saved = C.CACHE_DIR, os.environ.pop("ACWW_NO_REFERENCE_CACHE", None)
        C.CACHE_DIR = tmp / "cache"
        try:
            out, ram = tmp / "out", tmp / "out" / "ram"
            trace = out / "crossings.bin"
            log = b"frames: sequence sha1 0\n  12  alpha\n  3 alpha+0x10 (beta+0x4?) 1=alphabet\nbranch to gamma.\n"
            seen = b"main 02000100 alpha\r\nov001 02000200 beta\r\n"  # (as the runtime writes it on Windows)

            def fresh() -> None:
                shutil.rmtree(out, ignore_errors=True)
                ram.mkdir(parents=True)
                (out / "reference.log").write_bytes(log)
                (out / "functions-seen.txt").write_bytes(seen)
                (out / "reference-hashes.txt").write_bytes(b"frame 0 a b\n")
                trace.write_bytes(bytes(40))
            before = run.policy_names(POLICY)
            fresh()
            run.keep_reference("cd" * 20, out, ram, trace, before)
            # alpha and beta change places, and the helper is renamed
            after = run.policy_names(POLICY.replace("alpha", "x").replace("beta", "alpha").replace(" x ", " beta ")
                                     .replace("_dadd", "gamma"))
            if not run.reference_cached("cd" * 20, out, ram, trace, after):
                bad.append("an entry of other names did not come back")
            want = b"frames: sequence sha1 0\n  12  beta\n  3 beta+0x10 (alpha+0x4?) 1=alphabet\nbranch to gamma.\n"
            if (out / "reference.log").read_bytes() != want:
                bad.append(f"the log came back as {(out / 'reference.log').read_bytes()!r}")
            if (out / "functions-seen.txt").read_bytes() != b"main 02000100 beta\r\nov001 02000200 alpha\r\n":
                bad.append(f"the list came back as {(out / 'functions-seen.txt').read_bytes()!r}")
            if run.reference_differs("cd" * 20, out, ram, trace, after):
                bad.append(f"the renamed entry differs from itself: {run.reference_differs('cd' * 20, out, ram, trace, after)}")
            fresh()  # the names of before: a run under the new names would not give this
            if sorted(run.reference_differs("cd" * 20, out, ram, trace, after)) != ["functions-seen.txt", "reference.log"]:
                bad.append(f"stale names not told: {run.reference_differs('cd' * 20, out, ram, trace, after)}")
            if not run.reference_cached("cd" * 20, out, ram, trace, before) or (out / "reference.log").read_bytes() != log:
                bad.append("the entry did not come back under its own names")
            # one name for two functions that now have different names: a word could be either
            both = run.policy_names(POLICY.replace("beta", "alpha"))
            fresh()
            run.keep_reference("ef" * 20, out, ram, trace, both)
            if run.reference_cached("ef" * 20, out, ram, trace, before):
                bad.append("an entry whose names cannot be told apart was used")
            if not run.reference_cached("ef" * 20, out, ram, trace, both):
                bad.append("an entry did not come back under its own (repeated) names")
            other = run.policy_names(POLICY + "02000400 main 8 N delta 0 0 -1 -1 -1 0 0\n")
            if run.reference_cached("cd" * 20, out, ram, trace, other):
                bad.append("an entry of another set of functions was used")
            fresh()
            run.keep_reference("01" * 20, out, ram, trace)  # (kept without names)
            if run.reference_cached("01" * 20, out, ram, trace, before) or not run.reference_cached("01" * 20, out, ram, trace):
                bad.append("an entry without names: used with names, or not used without")
        finally:
            C.CACHE_DIR = saved[0]
            if saved[1] is not None:
                os.environ["ACWW_NO_REFERENCE_CACHE"] = saved[1]
    return bad


def main() -> int:
    bad = check_entries() + check_scope() + check_entry() + check_facts() + check_names()
    for line in bad:
        print(f"FAIL: {line}")
    print("the Reference cache's key and entries: " + ("FAIL" if bad else "ok"))
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
