"""Draw the progress maps: treemaps of the ARM9 code, one tile per module sized by code bytes,
each function coloured by its level.

docs/progress-decomp.svg, the decompilation:

    linked     Linked: the whole program, linked with the original linker, also reproduces the
               module byte for byte (build/adm-kr/linked.json, a list of source paths)
    native     Matching: a source compiles to the ROM's bytes and links to its targets (verify.py)
    reference  Reference only: no matching source (left out of the legend when there is none)

docs/progress-clean.svg, how each function's Clean version is checked:

    function   Checked by function: `tools/diffcheck.py --native --clean` ran it against the
               ROM's code and it agrees (build/adm-kr/clean-checked.json)
    run        Checked in a run: it ran in a recording run (`tools/run.py ... --clean
               --clean-ran`) whose frames and memory match the Reference
               (build/adm-kr/clean-ran.json, merged from the runs by --merge-ran)
    driven     Checked by a driven call: no game path calls it, and a driven call
               (`tools/driven.py`, docs/verification.md) ran it on a live object in a scene's
               run, whose memory after the call and frames match the Reference
               (runtime/recordings/scenes/clean-driven.txt)
    read       Read only: checked only by reading it against its matching source
    none       No Clean version (left out of the legend when there is none)

Each function counts at the highest level it reached. The Clean map's legend also gives the
functions checked in a run or by a driven call, whatever their level: the goal's checked set
(clean-ran.json, which takes runtime/recordings/scenes/clean-entered.txt, and clean-driven.txt).

    python tools/verify.py && python tools/progress_map.py
    python tools/progress_map.py --merge-ran title.json new-game.json   # build/adm-kr/clean-ran.json
    python tools/progress_map.py --merge-ran title.json runtime/recordings/scenes/clean-entered.txt
                                 # (one command) with the scenes' list (tools/coverage.py --record)
"""

from __future__ import annotations

import html
import json
import os
import pathlib
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import common as C  # noqa: E402
import report as R  # noqa: E402

DECOMP_OUT = C.ROOT / "docs" / "progress-decomp.svg"
CLEAN_OUT = C.ROOT / "docs" / "progress-clean.svg"


class Map:
    def __init__(self, title: str, levels: tuple[str, ...], colors: dict[str, str], labels: dict[str, str],
                 optional: set[str]):
        self.title, self.levels, self.colors, self.labels = title, levels, colors, labels
        self.optional = optional  # shown in the legend only when some function has it


DECOMP = Map("Decompilation", ("linked", "native", "reference"),
             {"linked": "#2bb673", "native": "#3a86d4", "reference": "#323b46"},
             {"linked": "Linked", "native": "Matching", "reference": "Reference only"}, {"reference"})
CLEAN = Map("Clean code", ("function", "run", "driven", "read", "none"),
            {"function": "#f0b429", "run": "#a371f7", "driven": "#5e7bd6", "read": "#323b46", "none": "#1f252c"},
            {"function": "Checked by function", "run": "Checked in a run", "driven": "Checked by a driven call",
             "read": "Read only", "none": "No Clean version"}, {"none", "driven"})
DRIVEN = C.ROOT / "runtime" / "recordings" / "scenes" / "clean-driven.txt"
BG, CARD, FG, MUTED = "#0d1117", "#161b22", "#e6edf3", "#8b949e"

W = 960
PAD = 20
HEAD = 112          # title, overall bar and legend
LEGEND_ROW = 20     # each legend row after the first (the legend wraps)
MAP_H = 440
LIB_W = 120         # the libraries strip on the right
FOOT = 26
H = HEAD + MAP_H + FOOT + PAD


def squarify(items: list[tuple[str, float]], x: float, y: float, w: float, h: float):
    """Squarified treemap (Bruls, Huizing, van Wijk 2000): yields (key, x, y, w, h)."""
    items = sorted((kv for kv in items if kv[1] > 0), key=lambda kv: -kv[1])
    total = sum(v for _, v in items)
    if not items:
        return
    scale = w * h / total
    rest = [(k, v * scale) for k, v in items]
    while rest:
        short = min(w, h)
        row, worst = [], float("inf")
        while rest:
            cand = row + [rest[0]]
            s = sum(a for _, a in cand)
            ratio = max(max(short * short * a / (s * s), s * s / (short * short * a))
                        for _, a in cand)
            if ratio > worst:
                break
            row, worst = cand, ratio
            rest.pop(0)
        s = sum(a for _, a in row)
        if w >= h:
            cw, cy = s / h, y
            for k, a in row:
                yield k, x, cy, cw, a / cw
                cy += a / cw
            x, w = x + cw, w - cw
        else:
            rh, cx = s / w, x
            for k, a in row:
                yield k, cx, y, a / rh, rh
                cx += a / rh
            y, h = y + rh, h - rh


def load_list(name: str) -> list:
    path = C.BUILD / name
    return json.loads(path.read_text()) if path.exists() else []


def keys(rows: list) -> set[tuple[str, int]]:
    """(module, address) of each {"module", "address"} entry; an entry with "ran": false is
    left out."""
    return {(c["module"], int(c["address"], 16) if isinstance(c["address"], str) else c["address"])
            for c in rows if c.get("ran", True)}


def clean_versions() -> set[tuple[str, int]]:
    """Every function with a Clean version: registered with CLEAN_AS or checked in tests/clean/."""
    import run  # noqa: PLC0415 (heavier: only for the Clean map)
    out = {(module, address & ~1) for _, _, module, address, _ in run.clean_registrations("all")}
    return out | {(module, address & ~1) for _, module, address, _ in run.clean_checks("all")}


def classify(level_of) -> tuple[dict[str, dict[str, int]], dict[str, int], dict[str, int],
                                dict[str, list[tuple[int, str]]]]:
    """(game module -> level -> bytes, level -> function count, libs module -> bytes,
    game module -> [(size, level)] in address order), with `level_of(module, function)`."""
    game: dict[str, dict[str, int]] = {}
    counts: dict[str, int] = {}
    libs: dict[str, int] = {}
    order: dict[str, list[tuple[int, str]]] = {}
    for (cat, mod), funcs in R.functions().items():
        if cat == "libs":
            libs[mod] = libs.get(mod, 0) + sum(f["size"] for f in funcs)
            continue
        per = game.setdefault(mod, {})
        seq = order.setdefault(mod, [])
        for f in sorted(funcs, key=lambda f: f["address"]):
            level = level_of(mod, f)
            per[level] = per.get(level, 0) + f["size"]
            counts[level] = counts.get(level, 0) + 1
            seq.append((f["size"], level))
    return game, counts, libs, order


CELL = 90.0         # target area of one cell, in square pixels


def cells(seq: list[tuple[int, str]], n: int) -> list[tuple[int, str]]:
    """Cut the address-ordered functions into about `n` runs of equal bytes; each run takes
    the level holding most of its bytes."""
    total = sum(sz for sz, _ in seq) or 1
    step = total / max(1, n)
    out, acc, cur = [], 0, {}
    for sz, level in seq:
        cur[level] = cur.get(level, 0) + sz
        acc += sz
        if acc >= step:
            out.append((acc, max(cur, key=cur.get)))
            acc, cur = 0, {}
    if acc:
        out.append((acc, max(cur, key=cur.get)))
    return out


def tile(parts: list[str], colors: dict[str, str], key: str, seq: list[tuple[int, str]], x: float, y: float,
         w: float, h: float, label: str, tip: str) -> None:
    gap = 2.0
    x, y, w, h = x + gap, y + gap, max(0.0, w - 2 * gap), max(0.0, h - 2 * gap)
    if w < 1 or h < 1:
        return
    clip = f"c-{key}"
    parts.append(f'<clipPath id="{clip}"><rect x="{x:.1f}" y="{y:.1f}" width="{w:.1f}" '
                 f'height="{h:.1f}" rx="4"/></clipPath><g clip-path="url(#{clip})">'
                 f'<rect x="{x:.1f}" y="{y:.1f}" width="{w:.1f}" height="{h:.1f}" fill="{BG}"/>')
    runs = cells(seq, int(w * h / CELL))
    items = [(i, sz) for i, (sz, _) in enumerate(runs)]
    for i, cx, cy, cw, ch in squarify(items, x, y, w, h):
        level = runs[i][1]
        parts.append(f'<rect x="{cx + 0.4:.1f}" y="{cy + 0.4:.1f}" width="{max(0.2, cw - 0.8):.1f}" '
                     f'height="{max(0.2, ch - 0.8):.1f}" fill="{colors[level]}"/>')
    parts.append("</g>")
    parts.append(f'<rect x="{x:.1f}" y="{y:.1f}" width="{w:.1f}" height="{h:.1f}" rx="4" '
                 f'fill="none" stroke="#ffffff" stroke-opacity="0.10">'
                 f"<title>{html.escape(tip)}</title></rect>")
    if w > 44 and h > 20:
        size = 13 if w > 120 and h > 44 else 10
        tw = size * 0.62 * len(label) + 10
        parts.append(f'<rect x="{x + 3:.1f}" y="{y + 3:.1f}" width="{tw:.1f}" '
                     f'height="{size + 7:.1f}" rx="3" fill="{BG}" fill-opacity="0.72"/>')
        parts.append(f'<text x="{x + 8:.1f}" y="{y + size + 5:.1f}" font-size="{size}" '
                     f'font-weight="600" fill="{FG}">{html.escape(label)}</text>')


def draw(spec: Map, level_of, out: pathlib.Path, footer: str, extra: str = "") -> dict[str, int]:
    game, counts, libs, order = classify(level_of)
    levels = [lv for lv in spec.levels if lv not in spec.optional or counts.get(lv)]
    total = {lv: sum(m.get(lv, 0) for m in game.values()) for lv in spec.levels}
    all_bytes = sum(total.values()) or 1
    nfuncs = sum(counts.values())
    bottom = spec.levels[-1] if spec.levels[-1] in levels else levels[-1]
    items = [(spec.colors[lv], f"{spec.labels[lv]}  {100 * total[lv] / all_bytes:.1f}%  ({counts.get(lv, 0):,})")
             for lv in levels] + ([(None, extra)] if extra else [])
    rows, x = 0, PAD
    for color, text in items:
        width = (18 if color else 0) + 7 * len(text)
        if x > PAD and x + width > W - PAD:
            rows, x = rows + 1, PAD
        x += 16 + width
    head, height = HEAD + LEGEND_ROW * rows, H + LEGEND_ROW * rows
    p: list[str] = [
        f'<svg xmlns="http://www.w3.org/2000/svg" width="{W}" height="{height}" '
        f'viewBox="0 0 {W} {height}" font-family="ui-sans-serif,-apple-system,Segoe UI,Helvetica,'
        f'Arial,sans-serif">',
        f'<rect width="{W}" height="{height}" rx="12" fill="{BG}"/>',
        f'<rect x="1" y="1" width="{W - 2}" height="{height - 2}" rx="11" fill="{CARD}" '
        f'stroke="#30363d"/>',
        f'<text x="{PAD}" y="{PAD + 18}" font-size="18" font-weight="700" fill="{FG}">'
        f"{html.escape(spec.title)}: Animal Crossing: Wild World (ARM9 game code)</text>",
        f'<text x="{W - PAD}" y="{PAD + 18}" font-size="12" fill="{MUTED}" text-anchor="end">'
        f"{nfuncs:,} functions, {all_bytes / 1024:,.0f} KB</text>",
    ]
    # overall bar
    bx, by, bw, bh = PAD, PAD + 34, W - 2 * PAD, 12
    p.append(f'<clipPath id="bar"><rect x="{bx}" y="{by}" width="{bw}" height="{bh}" rx="6"/>'
             f'</clipPath><g clip-path="url(#bar)"><rect x="{bx}" y="{by}" width="{bw}" '
             f'height="{bh}" fill="{spec.colors[bottom]}"/>')
    off = 0.0
    for level in spec.levels:
        seg = bw * total[level] / all_bytes
        if seg > 0 and level != bottom:
            p.append(f'<rect x="{bx + off:.1f}" y="{by}" width="{seg:.1f}" height="{bh}" '
                     f'fill="{spec.colors[level]}"/>')
        off += seg
    p.append("</g>")
    # legend: the levels, then `extra` (bold, no swatch), in rows that wrap
    lx, ly = PAD, by + bh + 30
    for color, text in items:
        width = (18 if color else 0) + 7 * len(text)
        if lx > PAD and lx + width > W - PAD:
            lx, ly = PAD, ly + LEGEND_ROW
        if color:
            p.append(f'<rect x="{lx}" y="{ly - 10}" width="12" height="12" rx="3" fill="{color}"/>')
        weight = "" if color else ' font-weight="600"'
        p.append(f'<text x="{lx + (18 if color else 0)}" y="{ly}" font-size="12"{weight} fill="{FG}">'
                 f"{html.escape(text)}</text>")
        lx += 16 + width
    # game treemap
    mx, my, mw = PAD, head, W - 2 * PAD - LIB_W - 10
    for mod, x, y, w, h in squarify([(m, sum(v.values())) for m, v in game.items()],
                                    mx, my, mw, MAP_H):
        shares = game[mod]
        size = sum(shares.values())
        tip = (f"{mod}: {size:,} bytes; " + ", ".join(
            f"{spec.labels[lv]} {100 * shares[lv] / size:.1f}%" for lv in spec.levels if shares.get(lv)))
        tile(p, spec.colors, mod, order[mod], x, y, w, h, mod, tip)
    # libraries strip
    lx0 = W - PAD - LIB_W
    lib_total = sum(libs.values())
    p.append(f'<text x="{lx0}" y="{head - 6}" font-size="11" fill="{MUTED}">'
             f"Libraries (not included)</text>")
    lib_colors = {"lib": DECOMP.colors["reference"]}
    for mod, x, y, w, h in squarify(list(libs.items()), lx0, head, LIB_W, MAP_H):
        tile(p, lib_colors, "lib-" + mod, [(libs[mod], "lib")], x, y, w, h, mod,
             f"{mod} (libraries): {libs[mod]:,} bytes")
    foot = (f"Tile area is code size. {footer}" if footer else
            f"Tile area is code size. Libraries: {lib_total / 1024:,.0f} KB (NitroSDK, NitroSystem, "
            f"NitroDWC, NitroWiFi, GameSpy, MSL), see libs/README.md.")
    p.append(f'<text x="{PAD}" y="{height - PAD + 4}" font-size="11" fill="{MUTED}">{html.escape(foot)}</text>')
    p.append("</svg>")
    out.write_text("\n".join(p) + "\n", encoding="utf-8", newline="\n")
    print(f"{out.relative_to(C.ROOT)}: " + ", ".join(
        f"{spec.labels[lv]} {100 * total[lv] / all_bytes:.1f}% ({counts.get(lv, 0):,})" for lv in levels)
        + (f"; {extra}" if extra else ""))
    return counts


def kept_reference() -> int:
    """How many functions the PC runtime keeps Reference (runtime/native-reference.txt and
    tools/native.py's keep-reference.txt): their Clean versions cannot run there either."""
    names = set()
    for path in (C.ROOT / "runtime" / "native-reference.txt",
                 C.BUILD / "native" / ("windows" if os.name == "nt" else "linux") / "keep-reference.txt"):
        for line in path.read_text().splitlines() if path.exists() else []:
            if line.strip() and not line.startswith("#"):
                names.add(line.split()[0])
    game = {f["name"] for (cat, _), funcs in R.functions().items() if cat != "libs" for f in funcs}
    return len(names & game)


def merge_ran(paths: list[str]) -> None:
    """build/adm-kr/clean-ran.json: the runs' lists (tools/run.py --clean-ran), a function
    counting as ran when it ran in any of them."""
    ran: dict[tuple[str, str], bool] = {}
    for path in map(pathlib.Path, paths):
        if not path.exists():
            print(f"{path}: missing, left out")
            continue
        if path.suffix == ".txt":  # "module address" lines: functions that ran
            rows = [{"module": m, "address": a} for m, a in
                    (line.split()[:2] for line in path.read_text().splitlines()
                     if line.strip() and not line.startswith("#"))]
        else:
            rows = json.loads(path.read_text())
        for row in rows:
            key = (row["module"], row["address"])
            ran[key] = ran.get(key, False) or bool(row.get("ran", True))
    rows = [{"module": m, "address": a, "ran": r} for (m, a), r in sorted(ran.items())]
    (C.BUILD / "clean-ran.json").write_text(json.dumps(rows, indent=1) + "\n", newline="\n")
    print(f"build/adm-kr/clean-ran.json: {sum(ran.values())} of {len(ran)} Clean functions ran")


def main() -> None:
    if sys.argv[1:2] == ["--merge-ran"]:
        merge_ran(sys.argv[2:])
        return
    linked = set(load_list("linked.json"))

    def decomp_level(_mod: str, f: dict) -> str:
        if f["complete"] and f["file"] in linked:
            return "linked"
        return "native" if f["complete"] else "reference"

    draw(DECOMP, decomp_level, DECOMP_OUT, "")
    checked = keys(load_list("clean-checked.json"))
    ran = keys(load_list("clean-ran.json"))
    driven = {(m, int(a, 16)) for m, a in (line.split()[:2] for line in
                                            (DRIVEN.read_text().splitlines() if DRIVEN.exists() else [])
                                            if line.strip() and not line.startswith("#"))}
    versions = clean_versions()

    def clean_level(mod: str, f: dict) -> str:
        key = (mod, f["address"])
        if key in checked:
            return "function"
        if key in ran:
            return "run"
        if key in driven:
            return "driven"
        return "read" if key in versions else "none"

    kept = kept_reference()
    # checked: entered in a run or by a driven call, whatever level the function counts at
    entered = {k for k in versions if k in ran or k in driven}
    draw(CLEAN, clean_level, CLEAN_OUT,
         f"On the PC, {kept:,} functions stay Reference (hardware, the ROM's stack layout), and so do "
         f"their Clean versions." if kept else "",
         f"Checked (in a run or by a driven call): {len(entered):,} of {len(versions):,}")


if __name__ == "__main__":
    main()
