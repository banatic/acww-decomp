"""Draw docs/progress.svg: one rectangle per module, sized by code size, split into
clean, FAKEMATCH, failing LINK and not decompiled. Game code and library code are drawn
as separate panels. Git-ignored sources (GameSpy) count as not decompiled.

    python tools/verify.py && python tools/progress_map.py
"""

from __future__ import annotations

import html
import pathlib
import subprocess
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import common as C  # noqa: E402
import report as R  # noqa: E402

OUT = C.ROOT / "docs" / "progress.svg"
WIDTH, HEIGHT, LEGEND, TITLE, GAP = 960, 520, 44, 22, 8
KINDS = ("clean", "fake", "link", "none")
COLORS = {"clean": "#3f9b5a", "fake": "#d9a33a", "link": "#c8553d", "none": "#4a5560"}
LABELS = {"clean": "matching", "fake": "matching (FAKEMATCH)", "link": "LINK fails",
          "none": "not decompiled"}
PANELS = {"game": "Game", "libs": "Libraries"}
BG, FG, EDGE = "#0f1720", "#e6edf3", "#0f1720"


def squarify(items: list[tuple[str, float]], x: float, y: float, w: float, h: float):
    """Squarified treemap (Bruls, Huizing, van Wijk 2000): yields (key, x, y, w, h)."""
    items = sorted(items, key=lambda kv: -kv[1])
    total = sum(v for _, v in items)
    if not items or total <= 0:
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
        if w >= h:                      # lay the row out as a column on the left
            cw, cy = s / h, y
            for k, a in row:
                yield k, x, cy, cw, a / cw
                cy += a / cw
            x, w = x + cw, w - cw
        else:                           # ... or as a row along the top
            rh, cx = s / w, x
            for k, a in row:
                yield k, cx, y, a / rh, rh
                cx += a / rh
            y, h = y + rh, h - rh


def ignored(files: list[str]) -> set[str]:
    """The subset of repository-relative paths that git ignores (NUL-separated I/O, so
    Windows newline translation cannot mangle the paths)."""
    try:
        out = subprocess.run(["git", "check-ignore", "--stdin", "-z"],
                             input="\0".join(files).encode(), cwd=C.ROOT,
                             capture_output=True).stdout.decode()
    except OSError:
        return set()
    return {f for f in out.split("\0") if f}


def classify() -> dict[str, dict[str, dict[str, int]]]:
    """category -> module -> kind -> bytes."""
    fake_cache: dict[str, bool] = {}
    funcs_by = R.functions()
    hidden = ignored([f["file"] for fs in funcs_by.values() for f in fs if f.get("file")])

    def fake(rel: str) -> bool:
        if rel not in fake_cache:
            p = C.ROOT / rel
            fake_cache[rel] = p.exists() and "FAKEMATCH" in p.read_text(encoding="utf-8",
                                                                         errors="replace")
        return fake_cache[rel]

    per: dict[str, dict[str, dict[str, int]]] = {k: {} for k in PANELS}
    for (cat, mod), funcs in funcs_by.items():
        cats = per[cat].setdefault(mod, dict.fromkeys(KINDS, 0))
        for f in funcs:
            kind = ("none" if not f["matched"] or f.get("file") in hidden else "link" if not f["complete"]
                    else "fake" if fake(f["file"]) else "clean")
            cats[kind] += f["size"]
    return per


def draw_panel(parts: list[str], per: dict[str, dict[str, int]], x0: float, w0: float,
               title: str, dashed: bool) -> None:
    total = sum(sum(v.values()) for v in per.values())
    done = sum(v["clean"] + v["fake"] for v in per.values())
    parts.append(f'<text x="{x0 + 4:.1f}" y="15" font-size="13" fill="{FG}" '
                 f'font-weight="700">{html.escape(title)}</text>')
    parts.append(f'<text x="{x0 + w0 - 4:.1f}" y="15" font-size="12" fill="{FG}" '
                 f'text-anchor="end">{total / 1024:,.0f} KB, '
                 f'{100 * done / max(1, total):.1f}% matching</text>')
    y0, h0 = TITLE, HEIGHT - TITLE
    sizes = [(m, sum(v.values())) for m, v in per.items()]
    for mod, x, y, w, h in squarify(sizes, x0, y0, w0, h0):
        cats = per[mod]
        tot = sum(cats.values())
        off = 0.0
        # Inside a module the shares are stacked along its longer side.
        for kind in KINDS:
            share = cats[kind] / tot
            if share <= 0:
                continue
            if w >= h:
                parts.append(f'<rect x="{x + off * w:.1f}" y="{y:.1f}" width="{share * w:.1f}" '
                             f'height="{h:.1f}" fill="{COLORS[kind]}"/>')
            else:
                parts.append(f'<rect x="{x:.1f}" y="{y + off * h:.1f}" width="{w:.1f}" '
                             f'height="{share * h:.1f}" fill="{COLORS[kind]}"/>')
            off += share
        pct = 100 * cats["clean"] / tot
        dash = ' stroke-dasharray="4 2"' if dashed else ""
        parts.append(f'<rect x="{x:.1f}" y="{y:.1f}" width="{w:.1f}" height="{h:.1f}" '
                     f'fill="none" stroke="{EDGE}" stroke-width="1.5"{dash}>'
                     f'<title>{html.escape(title)} {html.escape(mod)}: {tot:,} bytes, '
                     f'{pct:.1f}% clean</title></rect>')
        if w > 46 and h > 18:
            size = 13 if w > 110 and h > 34 else 10
            parts.append(f'<text x="{x + 5:.1f}" y="{y + size + 3:.1f}" font-size="{size}" '
                         f'fill="{FG}" font-weight="600">{html.escape(mod)}</text>')


def main() -> None:
    per = classify()
    bytes_of = {k: sum(sum(v.values()) for v in per[k].values()) for k in PANELS}
    allb = sum(bytes_of.values())
    parts = [f'<svg xmlns="http://www.w3.org/2000/svg" width="{WIDTH}" '
             f'height="{HEIGHT + LEGEND}" viewBox="0 0 {WIDTH} {HEIGHT + LEGEND}" '
             f'font-family="ui-sans-serif,Segoe UI,Helvetica,Arial,sans-serif">',
             f'<rect width="100%" height="100%" fill="{BG}"/>']
    # Panel widths follow their byte counts, so one pixel of area is the same number of
    # bytes in both.
    inner = WIDTH - 4 - GAP
    x = 2.0
    for cat, title in PANELS.items():
        w = inner * bytes_of[cat] / allb
        draw_panel(parts, per[cat], x, w, title, cat == "libs")
        x += w + GAP

    totals = {k: sum(v[k] for p in per.values() for v in p.values()) for k in KINDS}
    lx, ly = 12, HEIGHT + 26
    for kind in KINDS:
        label = f"{LABELS[kind]} {100 * totals[kind] / allb:.1f}%"
        parts.append(f'<rect x="{lx}" y="{ly - 11}" width="12" height="12" '
                     f'fill="{COLORS[kind]}"/>')
        parts.append(f'<text x="{lx + 18}" y="{ly}" font-size="13" fill="{FG}">{label}</text>')
        lx += 30 + 7 * len(label)
    parts.append(f'<text x="{WIDTH - 12}" y="{ly}" font-size="13" fill="{FG}" '
                 f'text-anchor="end">ARM9 code, {allb / 1024:,.0f} KB, area = bytes</text>')
    parts.append("</svg>")
    OUT.parent.mkdir(exist_ok=True)
    OUT.write_text("\n".join(parts) + "\n", encoding="utf-8", newline="\n")
    print(f"{OUT.relative_to(C.ROOT)}: "
          + "; ".join(f"{t} {bytes_of[c]:,} bytes in {len(per[c])} modules"
                      for c, t in PANELS.items())
          + "; " + ", ".join(f"{k} {100 * v / allb:.1f}%" for k, v in totals.items()))


if __name__ == "__main__":
    main()
