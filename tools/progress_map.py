"""Draw docs/progress.svg: a treemap of the ARM9 code, one tile per module sized by code
bytes, coloured by how far each function has come.

    reference  only the ROM's code exists
    native     a source compiles to the ROM's bytes and links to its targets (verify.py)
    linked     ... and the whole program, linked with the original linker, reproduces the
               module byte for byte (build/adm-kr/linked.json, a list of source paths)
    clean      a readable implementation passes the differential check against the
               reference (build/adm-kr/clean.json, a list of {"module", "address"})

Each function counts at the highest level it reached.

    python tools/verify.py && python tools/progress_map.py
"""

from __future__ import annotations

import html
import json
import pathlib
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import common as C  # noqa: E402
import report as R  # noqa: E402

OUT = C.ROOT / "docs" / "progress.svg"

LEVELS = ("clean", "linked", "native", "reference")
COLORS = {"clean": "#f0b429", "linked": "#2bb673", "native": "#3a86d4", "reference": "#323b46"}
LABELS = {"clean": "Clean", "linked": "Native, linked", "native": "Native",
          "reference": "Reference only"}
BG, CARD, FG, MUTED = "#0d1117", "#161b22", "#e6edf3", "#8b949e"

W = 960
PAD = 20
HEAD = 112          # title, overall bar and legend
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


def classify() -> tuple[dict[str, dict[str, int]], dict[str, int], dict[str, int],
                       dict[str, list[tuple[int, str]]]]:
    """(game module -> level -> bytes, level -> function count, libs module -> bytes,
    game module -> [(size, level)] in address order)."""
    linked = set(load_list("linked.json"))
    clean = {(c["module"], int(c["address"], 16) if isinstance(c["address"], str) else c["address"])
             for c in load_list("clean.json")}
    game: dict[str, dict[str, int]] = {}
    counts = dict.fromkeys(LEVELS, 0)
    libs: dict[str, int] = {}
    order: dict[str, list[tuple[int, str]]] = {}
    for (cat, mod), funcs in R.functions().items():
        if cat == "libs":
            libs[mod] = libs.get(mod, 0) + sum(f["size"] for f in funcs)
            continue
        per = game.setdefault(mod, dict.fromkeys(LEVELS, 0))
        seq = order.setdefault(mod, [])
        for f in sorted(funcs, key=lambda f: f["address"]):
            if (mod, f["address"]) in clean:
                level = "clean"
            elif f["complete"] and f["file"] in linked:
                level = "linked"
            elif f["complete"]:
                level = "native"
            else:
                level = "reference"
            per[level] += f["size"]
            counts[level] += 1
            seq.append((f["size"], level))
    return game, counts, libs, order


CELL = 90.0         # target area of one cell, in square pixels


def cells(seq: list[tuple[int, str]], n: int) -> list[tuple[int, str]]:
    """Cut the address-ordered functions into about `n` runs of equal bytes; each run takes
    the level holding most of its bytes."""
    total = sum(sz for sz, _ in seq) or 1
    step = total / max(1, n)
    out, acc, cur = [], 0, dict.fromkeys(LEVELS, 0)
    for sz, level in seq:
        cur[level] += sz
        acc += sz
        if acc >= step:
            out.append((acc, max(cur, key=cur.get)))
            acc, cur = 0, dict.fromkeys(LEVELS, 0)
    if acc:
        out.append((acc, max(cur, key=cur.get)))
    return out


def tile(parts: list[str], key: str, seq: list[tuple[int, str]], x: float, y: float, w: float,
         h: float, label: str, tip: str) -> None:
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
                     f'height="{max(0.2, ch - 0.8):.1f}" fill="{COLORS[level]}"/>')
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


def main() -> None:
    game, counts, libs, order = classify()
    total = {lv: sum(m[lv] for m in game.values()) for lv in LEVELS}
    all_bytes = sum(total.values()) or 1
    nfuncs = sum(counts.values())
    p: list[str] = [
        f'<svg xmlns="http://www.w3.org/2000/svg" width="{W}" height="{H}" '
        f'viewBox="0 0 {W} {H}" font-family="ui-sans-serif,-apple-system,Segoe UI,Helvetica,'
        f'Arial,sans-serif">',
        f'<rect width="{W}" height="{H}" rx="12" fill="{BG}"/>',
        f'<rect x="1" y="1" width="{W - 2}" height="{H - 2}" rx="11" fill="{CARD}" '
        f'stroke="#30363d"/>',
        f'<text x="{PAD}" y="{PAD + 18}" font-size="18" font-weight="700" fill="{FG}">'
        f"Animal Crossing: Wild World (ARM9 game code)</text>",
        f'<text x="{W - PAD}" y="{PAD + 18}" font-size="12" fill="{MUTED}" text-anchor="end">'
        f"{nfuncs:,} functions, {all_bytes / 1024:,.0f} KB</text>",
    ]
    # overall bar
    bx, by, bw, bh = PAD, PAD + 34, W - 2 * PAD, 12
    p.append(f'<clipPath id="bar"><rect x="{bx}" y="{by}" width="{bw}" height="{bh}" rx="6"/>'
             f'</clipPath><g clip-path="url(#bar)"><rect x="{bx}" y="{by}" width="{bw}" '
             f'height="{bh}" fill="{COLORS["reference"]}"/>')
    off = 0.0
    for level in LEVELS[:-1]:
        seg = bw * total[level] / all_bytes
        if seg > 0:
            p.append(f'<rect x="{bx + off:.1f}" y="{by}" width="{seg:.1f}" height="{bh}" '
                     f'fill="{COLORS[level]}"/>')
        off += seg
    p.append("</g>")
    # legend
    lx, ly = PAD, by + bh + 30
    for level in LEVELS:
        pct = 100 * total[level] / all_bytes
        text = f"{LABELS[level]}  {pct:.1f}%  ({counts[level]:,})"
        p.append(f'<rect x="{lx}" y="{ly - 10}" width="12" height="12" rx="3" '
                 f'fill="{COLORS[level]}"/>')
        p.append(f'<text x="{lx + 18}" y="{ly}" font-size="12" fill="{FG}">'
                 f"{html.escape(text)}</text>")
        lx += 34 + 7 * len(text)
    # game treemap
    mx, my, mw = PAD, HEAD, W - 2 * PAD - LIB_W - 10
    for mod, x, y, w, h in squarify([(m, sum(v.values())) for m, v in game.items()],
                                    mx, my, mw, MAP_H):
        shares = game[mod]
        size = sum(shares.values())
        tip = (f"{mod}: {size:,} bytes; " + ", ".join(
            f"{LABELS[lv]} {100 * shares[lv] / size:.1f}%" for lv in LEVELS if shares[lv]))
        tile(p, mod, order[mod], x, y, w, h, mod, tip)
    # libraries strip
    lx0 = W - PAD - LIB_W
    lib_total = sum(libs.values())
    p.append(f'<text x="{lx0}" y="{HEAD - 6}" font-size="11" fill="{MUTED}">'
             f"Libraries (not included)</text>")
    for mod, x, y, w, h in squarify(list(libs.items()), lx0, HEAD, LIB_W, MAP_H):
        tile(p, "lib-" + mod, [(libs[mod], "reference")], x, y, w, h, mod,
             f"{mod} (libraries): {libs[mod]:,} bytes")
    p.append(f'<text x="{PAD}" y="{H - PAD + 4}" font-size="11" fill="{MUTED}">Tile area is code '
             f"size. Libraries: {lib_total / 1024:,.0f} KB (NitroSDK, NitroSystem, NitroDWC, "
             f"NitroWiFi, GameSpy, MSL), see libs/README.md.</text>")
    p.append("</svg>")
    OUT.write_text("\n".join(p) + "\n", encoding="utf-8", newline="\n")
    print(f"{OUT.relative_to(C.ROOT)}: " + ", ".join(
        f"{LABELS[lv]} {100 * total[lv] / all_bytes:.1f}%" for lv in LEVELS))


if __name__ == "__main__":
    main()
