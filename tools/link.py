"""Link the whole ARM9 program with the original linker and check it against the ROM.

    python tools/link.py
    python tools/link.py --why [FILE...]   # plan only: why each source stays out of the link

Every game source whose object can stand alone becomes a `complete` translation unit; the
rest of each module comes from ds-decomp's delinked objects. dsd writes the linker script,
mwldarm links, and `dsd check modules` compares every module with the ROM. On success the
linked sources are listed in build/adm-kr/linked.json (read by progress_map.py).

A source stays out of the link, with its reason counted, when:
- a section of its object has no place in the ROM, or two pointers place it differently;
- a section lands in another module, or in a ROM section of another kind;
- its same-named sections are not contiguous;
- a data range does not start and end on the ROM's symbol boundaries;
- it claims bytes another source claims;
- its data order contradicts its code order relative to the other sources (link order);
- a word outside it points into its data at an address it does not export;
- its code ends on a 2-byte boundary followed by a Thumb nop, which the compiler emits only
  between two functions of one object.

Needs ds-decomp's `dsd` (DSD; default build/tools/dsd, see INSTALL.md) and mwldarm from
MWCC_ROOT (1.2/base).
"""

from __future__ import annotations

import bisect
import collections
import concurrent.futures as cf
import json
import os
import pathlib
import re
import shlex
import shutil
import struct
import subprocess
import sys
import time

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import common as C  # noqa: E402
import verify as V  # noqa: E402

LINK = C.BUILD / "link"
CFG = LINK / "config" / "arm9"
DSD = pathlib.Path(os.environ.get("DSD", C.ROOT / "build" / "tools" / ("dsd.exe" if os.name == "nt" else "dsd")))
SECTION = re.compile(r"\s+(\.\w+)\s+start:0x([0-9a-f]+) end:0x([0-9a-f]+)")
SYMBOL = re.compile(r"(\S+) kind:(\w+)(?:\([^)]*\))? addr:0x([0-9a-f]+)")
RELOC = re.compile(r"from:0x([0-9a-f]+) kind:\w+ to:0x([0-9a-f]+) module:(\S+)")
ORDER = [".text", ".init", ".ctor", ".rodata", ".data", ".bss"]


def module_dir(root: pathlib.Path, module: str) -> pathlib.Path:
    return root / C.config_dir(module).relative_to(C.CONFIG)


def module_sections(module: str) -> list[tuple[str, int, int]]:
    rows = []
    for line in (C.config_dir(module) / "delinks.txt").read_text().splitlines():
        m = SECTION.match(line)
        if not m:
            break
        rows.append((m.group(1), int(m.group(2), 16), int(m.group(3), 16)))
    return rows


# ------------------------------------------------------------------------------ placement

class Planner:
    """Where each section of a source's object lands in the ROM. The function's section is
    at the function's address; any other section is placed by pointers the ROM holds into
    it, from the function's literal pool or from an already placed section."""

    def __init__(self):
        self.chk = V.Checker()
        self.sections = {m: module_sections(m) for m in self.chk.mods}

    def where(self, addr: int, prefer: str) -> tuple[str | None, str | None]:
        for m in (prefer, *C.RESIDENT, *self.sections):
            for name, a, b in self.sections.get(m, ()):
                if a <= addr < b:
                    return m, name
        return None, None

    def plan(self, path: pathlib.Path) -> dict | None:
        src = C.parse_source(path)
        if src is None:
            return None
        rel = path.relative_to(C.ROOT).as_posix()
        obj, _ = C.compile_source(src)
        if obj is None:
            return {"file": rel, "error": "does not compile"}
        elf = C.Elf(obj)
        fn = elf.function(src.object_symbol)
        if fn is None:
            return {"file": rel, "error": "function not in the object"}
        secs = {i: s for i, s in enumerate(elf.sections) if s.size and s.type in (1, 8)
                and not s.name.startswith((".comment", ".exceptix", ".exception"))}
        anchors = collections.defaultdict(set)
        anchors[fn.shndx].add(src.address - fn.value)
        work, done = [fn.shndx], set()
        while work:
            si = work.pop()
            if si in done:
                continue
            done.add(si)
            base = min(anchors[si])
            for off, typ, s, add in elf.relocations(si):
                if typ != 2 or s.shndx in (0, fn.shndx) or s.shndx not in secs:
                    continue
                word = self.chk.rom_abs(base + off, src.module, 4)
                if len(word) < 4:
                    continue
                value, = struct.unpack("<I", word)
                if s.type == 2:
                    value &= ~1
                anchors[s.shndx].add(value - (add or 0) - s.value)
                work.append(s.shndx)
        out = {"file": rel, "module": src.module, "sections": []}
        for si, s in secs.items():
            if not anchors.get(si):
                out["sections"].append([s.name, None, None, None, s.size])
                out["error"] = "a section has no place in the ROM"
                continue
            if len(anchors[si]) > 1:
                out["error"] = "pointers place a section differently"
            base = min(anchors[si])
            out["sections"].append([s.name, *self.where(base, src.module), base, base + s.size])
        out["globals"] = [[y.name, min(anchors[y.shndx]) + y.value] for y in elf.symbols
                          if y.bind == 1 and y.name and y.shndx in secs and y.shndx != fn.shndx
                          and anchors.get(y.shndx)]
        return out


# ------------------------------------------------------------------------------ choosing TUs

def reloc_modules(spec: str) -> list[str]:
    if spec == "main":
        return ["main"]
    if spec.startswith("overlay"):
        return [f"ov{int(x):03d}" for x in spec[spec.index("(") + 1:-1].split(",")]
    if spec.startswith("autoload"):
        return [f"autoload_{spec[spec.index('(') + 1:-1]}"]
    return [spec]


def longest_increasing(items: list[tuple[str, int]]) -> set[str]:
    """Names on a longest increasing run of `items` [(name, value)]."""
    tails, idx, prev = [], [], [None] * len(items)
    for i, (_, v) in enumerate(items):
        k = bisect.bisect_left(tails, v)
        if k == len(tails):
            tails.append(v)
            idx.append(i)
        else:
            tails[k] = v
            idx[k] = i
        prev[i] = idx[k - 1] if k else None
    keep, i = set(), idx[-1] if idx else None
    while i is not None:
        keep.add(items[i][0])
        i = prev[i]
    return keep


# source -> the reason it stays out of the link (filled by choose)
LEFT_OUT: dict[str, str] = {}


def choose(plans: list[dict], mods: dict) -> tuple[dict[str, list], collections.Counter]:
    """module -> [(file, {section: (start, end)})] of the sources that can be linked, and
    the reasons the others cannot (counted, and per source in LEFT_OUT)."""
    why: collections.Counter = collections.Counter()
    entries: dict[str, list] = collections.defaultdict(list)
    exported: dict[str, dict[int, str]] = {}
    for r in plans:
        if r.get("error"):
            why[r["error"]] += 1
            LEFT_OUT[r["file"]] = r["error"]
            continue
        secs: dict[str, list] = {}
        reason = None
        for name, mod, romsec, start, end in r["sections"]:
            if mod != r["module"]:
                reason = "data in another module"
            elif romsec != name:
                reason = f"{name} lands in {romsec}"
            if reason:
                break
            secs.setdefault(name, []).append((start, end))
        if not reason and any(not (a1 <= b0 <= (a1 + 3) & ~3)
                              for parts in secs.values()
                              for (_, a1), (b0, _) in zip(parts, parts[1:])):
            reason = "same-named sections not contiguous"
        if reason:
            why[reason] += 1
            LEFT_OUT[r["file"]] = reason
            continue
        entries[r["module"]].append((r["file"], {n: (p[0][0], p[-1][1]) for n, p in secs.items()}))
        exported[r["file"]] = {a: n for n, a in r["globals"]}

    bad: set[str] = set()

    def drop(f: str, reason: str) -> None:
        if f not in bad:
            bad.add(f)
            why[reason] += 1
            LEFT_OUT[f] = reason

    refs: dict[str, list] = collections.defaultdict(list)
    for p in C.CONFIG.rglob("relocs.txt"):
        for line in p.read_text().splitlines():
            m = RELOC.match(line)
            if m and m.group(3) != "none":
                for mod in reloc_modules(m.group(3)):
                    refs[mod].append((int(m.group(2), 16), int(m.group(1), 16)))
    for mod, es in entries.items():
        bounds = {x for _, a, b in module_sections(mod) for x in (a, b)}
        names: dict[int, str] = {}
        for line in (C.config_dir(mod) / "symbols.txt").read_text().splitlines():
            m = SYMBOL.match(line)
            if m:
                a = int(m.group(3), 16)
                names.setdefault(a, m.group(1))
                if m.group(2) in ("data", "bss"):
                    bounds.add(a)
        targets = sorted(refs[mod])
        keys = [t for t, _ in targets]
        img, base = C.module_image(mod), mods[mod]["base"]
        for f, merged in es:
            _, end = merged.get(".text") or merged[".init"]  # an initialiser sits in .init
            if end % 4 == 2 and img[end - base:end - base + 2] == b"\xc0\x46":
                drop(f, "Thumb nop after the code: shares an object with what follows")
                continue
            spans = list(merged.values())
            for name, (x, y) in merged.items():
                if name in (".text", ".init"):
                    continue
                if x not in bounds or (y not in bounds and (y + 3) & ~3 not in bounds):
                    drop(f, "data size differs from the ROM's symbols")
                    break
                outside = [t for t, frm in targets[bisect.bisect_left(keys, x):bisect.bisect_left(keys, y)]
                           if not any(p <= frm < q for p, q in spans)]
                if any(exported[f].get(t) != names.get(t) for t in outside):
                    drop(f, "data used from outside but not exported")
                    break
        # an object's tail padding up to the next object belongs to it
        es[:] = [(f, {n: (a, (b + 3) & ~3) for n, (a, b) in m.items()}) for f, m in es]
        claims = sorted((a, b, f) for f, m in es if f not in bad for a, b in m.values())
        for (_, a1, f0), (b0, _, f1) in zip(claims, claims[1:]):
            if b0 < a1:
                drop(f0, "overlapping claims")
                drop(f1, "overlapping claims")
        for sec in ORDER[1:]:
            seq = sorted(((m.get(".text") or m[".init"])[0], f, m[sec][0]) for f, m in es if sec in m and f not in bad)
            keep = longest_increasing([(f, a) for _, f, a in seq])
            for _, f, _ in seq:
                if f not in keep:
                    drop(f, "link order")
    return {m: [e for e in es if e[0] not in bad] for m, es in entries.items()}, why


# ------------------------------------------------------------------------------ link

def write_config(entries: dict[str, list]) -> None:
    """A copy of config/ with build paths under build/adm-kr/link and the TUs appended."""
    if LINK.exists():
        shutil.rmtree(LINK)
    LINK.mkdir(parents=True)
    shutil.copytree(C.CONFIG, CFG)
    up = "../" * len(CFG.relative_to(C.ROOT).parts)
    text = (CFG / "config.yaml").read_text()
    text = re.sub(r"\.\./\.\./\.\./", up, text)
    text = re.sub(r"^build_path: .*$", f"build_path: {up}build/adm-kr/obj", text, flags=re.M)
    text = re.sub(r"^delinks_path: .*$", f"delinks_path: {up}build/adm-kr/link/delinks", text, flags=re.M)
    # mwldarm writes the modules to <build_path>/build
    text = text.replace(f"{up}build/adm-kr/build/", f"{up}build/adm-kr/obj/build/")
    (CFG / "config.yaml").write_text(text, newline="\n")
    for mod, es in entries.items():
        lines = []
        for f, merged in sorted(es, key=lambda e: (e[1].get(".text") or e[1][".init"])[0]):
            lines += [f"{f}:", "    complete"]
            for name in sorted(merged, key=lambda n: ORDER.index(n) if n in ORDER else 99):
                a, b = merged[name]
                lines.append(f"    {name:<11} start:0x{a:08x} end:0x{b:08x}")
            lines.append("")
        dl = module_dir(CFG, mod) / "delinks.txt"
        dl.write_text(dl.read_text().rstrip("\n") + "\n\n" + "\n".join(lines), newline="\n")


def step(what: str, t0: list[float] = [time.monotonic()]) -> None:
    now = time.monotonic()
    print(f"  {now - t0[0]:6.0f}s  {what}", flush=True)


def run(cmd: list[str], log: str) -> None:
    step(log.removesuffix(".log"))
    # mwldarm checks the same license file as the compiler
    env = dict(os.environ, LM_LICENSE_FILE=str(C.MWCC_ROOT / "license.dat"))
    p = subprocess.run(cmd, cwd=C.ROOT, capture_output=True, text=True, errors="replace", env=env)
    (LINK / log).write_text(p.stdout + p.stderr, newline="\n")
    if p.returncode != 0:
        tail = [line for line in (p.stdout + p.stderr).splitlines()
                if "multiply defined" not in line and "Ignoring the definition" not in line]
        raise SystemExit(f"{cmd[0]} failed (build/adm-kr/link/{log}):\n" + "\n".join(tail[-15:]))


def link() -> None:
    cfg = str(CFG / "config.yaml")
    if not (C.ROOT / "extract" / "adm-kr" / "config.yaml").exists():
        run([str(DSD), "rom", "extract", "-r", "extract/adm-kr.nds", "-o", "extract/adm-kr"],
            "extract.log")
    run([str(DSD), "delink", "-c", cfg], "delink.log")
    run([str(DSD), "lcf", "-c", cfg], "lcf.log")
    obj = C.BUILD / "obj"
    lcf = obj / "arm9.lcf"
    # absolute.txt: constants NitroSDK's linker script defines (stack sizes, overlay IDs, ...)
    defined = set(re.findall(r"^\s*(\w+)\s*=", lcf.read_text(), re.M))
    consts = [f"    {m.group(1)} = 0x{m.group(3)};"
              for line in (C.CONFIG / "absolute.txt").read_text().splitlines()
              if (m := SYMBOL.match(line)) and m.group(1) not in defined]
    lcf.write_text(lcf.read_text().replace("SECTIONS {", "SECTIONS {\n" + "\n".join(consts), 1),
                   newline="\n")
    out = obj / "build"
    if out.exists():
        shutil.rmtree(out)
    out.mkdir(parents=True)
    ld = C.MWCC_ROOT / "1.2" / "base" / "mwldarm.exe"
    # LD_WRAPPER runs the Windows linker elsewhere (default: MWCC_WRAPPER). wibo is slow here:
    # it scans the directories it opens files in, and the object tree has thousands of files.
    wrapper = shlex.split(os.environ.get("LD_WRAPPER", os.environ.get("MWCC_WRAPPER", "")))
    # -nodead: every gap object is reachable only through the ROM's own tables
    run([*wrapper, str(ld), "-proc", "arm946e", "-nodead", "-nostdlib", "-interworking",
         "-map", "closure,unused", "-m", "Entry", f"@{obj / 'objects.txt'}", str(lcf),
         "-o", str(obj / "arm9.o")], "link.log")
    run([str(DSD), "check", "modules", "-c", cfg, "--fail"], "check.log")


def main() -> None:
    # --why [FILE...]: plan only, and print why each named source (or every one left out) stays
    # out of the link; nothing is linked or written
    only = [pathlib.Path(a).as_posix() for a in sys.argv[2:]] if sys.argv[1:2] == ["--why"] else None
    planner = Planner()
    paths = [p for p in C.all_sources() if C.SRC in p.parents]
    with cf.ThreadPoolExecutor(max(1, (os.cpu_count() or 4) - 2)) as pool:
        plans = [r for r in pool.map(planner.plan, paths) if r]
    step(f"planned {len(plans)} sources")
    entries, why = choose(plans, planner.chk.mods)
    linked = sorted(f for es in entries.values() for f, _ in es)
    if only is not None:
        for f in only or sorted(LEFT_OUT):
            print(f"{f}: {LEFT_OUT.get(f, 'linked' if f in linked else 'not a planned source')}")
        return
    write_config(entries)
    # where each source's own data lands in the ROM, for the runtime's checks (tools/native.py)
    (C.BUILD / "placement.json").write_text(json.dumps(
        {r["file"]: [s for s in r["sections"] if s[0] not in (".text", ".init") and s[3] is not None]
         for r in plans if "sections" in r}) + "\n", newline="\n")
    (LINK / "left-out.txt").write_text("".join(f"{n:6} {k}\n" for k, n in why.most_common()),
                                       newline="\n")
    link()
    step("done")
    (C.BUILD / "linked.json").write_text(json.dumps(linked, indent=0) + "\n", newline="\n")
    print(f"{len(linked)} of {len(paths)} sources linked; every module matches the ROM")
    for k, n in why.most_common():
        print(f"  {n:6} left out: {k}")


if __name__ == "__main__":
    main()
