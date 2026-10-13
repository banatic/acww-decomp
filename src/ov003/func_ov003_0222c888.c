/* func_ov003_0222c888 @ 0x0222c888, 0x5c8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#pragma opt_loop_invariants off

typedef struct {
    char *buf;
    unsigned int w;
    unsigned int h;
} Grid;

extern int func_02037d9c(char *e);
extern u16 *func_0204f5e0(Grid *g, int cx, int cz, int dx, int dz, int layer);
extern int func_0204f294(Grid *g, int x, int y);
extern int func_02031b84(int x, int y);
extern int func_02031ba0(int x, int y);
extern int func_02031b5c(int x, int y);
extern int func_02031acc(int x, int y);
extern int func_ov003_02235518(int p1, u16 *o);
extern int func_ov003_0222c71c(u16 *o);
extern int func_ov003_0222c704(u16 *o);
extern int func_ov003_0222c6f0(u16 *o);
extern void func_ov003_0222c68c(int n, u16 *base, int *p2, int *p3);

int func_ov003_0222c888(char *p0, int p1, int *p2, int *p3, Grid *p4, int p5)
{
    int fj;
    u16 *base;
    int gh;
    int n0;
    int flag1;
    int hh;
    int flag2;
    int X;
    int fh;
    int fg;
    int gg;
    int Y;
    int j;
    int gf;
    int ff;
    int hg;
    int fe;
    int fd;
    int fc;
    int fb;
    int fa;
    int hf;
    int ge;
    int gd;
    int gc;
    int gb;
    int ga;
    int count;
    int he;
    int hd;
    int hc;
    int hb;
    int ha;
    u8 k;
    u16 *rowp;
    int wy;
    int wx;
    int i;
    int cx;
    int cz;
    unsigned int u;
    unsigned int v;
    char *e;
    u16 *o;
    u16 id;
    int f1;

    base = (u16 *) (p0 + ((*p2 + *p3 * 4) << 5));
    n0 = 0;
    count = 0;
    flag1 = 0;
    flag2 = 0;
    if (p5 == 6) {
        v = *p3 + 1;
        u = *p2 + 1;
        if (u < p4->w && v < p4->h && p4->buf != 0) {
            e = p4->buf + (u + v * p4->w) * 0x28;
        } else {
            e = 0;
        }
        if (e == 0) {
            return 0;
        }
        if ((func_02037d9c(e) & 0x100) != 0) {
            flag2 = 1;
        }
    }
    X = (*p2 + 1) << 4;
    Y = (*p3 + 1) << 4;
    j = 0;
    k = (u8) (char) (p1 - 2);
    do {
        i = 0;
        rowp = (u16 *) ((char *) base + j * 2);
        wy = Y + j;
        do {
            if (((*rowp >> i) & 1) != 0) {
                goto L_next;
            }
            wx = X + i;
            n0 = count;
            cx = wx >> 4;
            cz = wy >> 4;
            o = func_0204f5e0(p4, cx, cz, wx - (cx << 4), wy - (cz << 4), 0);
            if (o == 0) {
                goto L_inc;
            }
            switch (p5) {
                case 7:
                    if (p1 == 0x33) {
                        f1 = 0;
                        id = *o;
                        if (id >= 0x154a && id <= 0x1553) {
                            f1 = 1;
                        }
                        if (f1 == 0) {
                            if (!(id >= 0x1320 && id <= 0x1322)) {
                                goto L_c7b;
                            }
                        }
                        if (func_0204f294(p4, wx, wy) == 0) {
                            flag1 = 1;
                            count++;
                            break;
                        }
                    L_c7b:
                        if (*o == 0xfff1) {
                            count++;
                        }
                        break;
                    }
                    f1 = 0;
                    id = *o;
                    if (id >= 0x154a && id <= 0x1553) {
                        f1 = 1;
                    }
                    if (f1 == 0) {
                        break;
                    }
                    if (func_0204f294(p4, wx, wy) != 0) {
                        break;
                    }
                    count++;
                    break;
                case 4:
                    if (func_02031b84(wx, wy) == 0) {
                        break;
                    }
                    if (*o != 0xfff1) {
                        break;
                    }
                    count++;
                    break;
                case 6:
                    if (func_02031ba0(wx, wy) != 0) {
                        count++;
                        break;
                    }
                    if (flag2 == 0) {
                        break;
                    }
                    if (i <= 3) {
                        break;
                    }
                    if (j <= 3) {
                        break;
                    }
                    if (i >= 0xd) {
                        break;
                    }
                    if (j >= 0xd) {
                        break;
                    }
                    if (func_02031b5c(wx, wy) != 2) {
                        break;
                    }
                    count++;
                    break;
                case 1:
                    fj = 1;
                    fh = 1;
                    fg = 1;
                    ff = 1;
                    fe = 1;
                    fd = 1;
                    fc = 1;
                    fb = 1;
                    fa = 0;
                    id = *o;
                    if (id >= 0x26 && id <= 0x2a) {
                        fa = 1;
                    }
                    if (fa == 0) {
                        if (!(id >= 0x5d && id <= 0x61)) {
                            fb = 0;
                        }
                    }
                    if (fb == 0) {
                        if (!(id >= 0x2f && id <= 0x56)) {
                            fc = 0;
                        }
                    }
                    if (fc == 0) {
                        if (!(id >= 0x57 && id <= 0x5b)) {
                            fd = 0;
                        }
                    }
                    if (fd == 0) {
                        if (!(id >= 0x66 && id <= 0x68)) {
                            fe = 0;
                        }
                    }
                    if (fe == 0) {
                        if (id != 0x69) {
                            ff = 0;
                        }
                    }
                    if (ff == 0) {
                        if (!(id >= 0x6a && id <= 0x6c)) {
                            fg = 0;
                        }
                    }
                    if (fg == 0) {
                        if (id != 0x6d) {
                            fh = 0;
                        }
                    }
                    if (fh == 0) {
                        if (!(id >= 0xc8 && id <= 0xcf)) {
                            fj = 0;
                        }
                    }
                    if (fj != 0) {
                        break;
                    }
                    if (flag1 == 0) {
                        gh = 1;
                        gg = 1;
                        gf = 1;
                        ge = 1;
                        gd = 1;
                        gc = 1;
                        gb = 1;
                        ga = 0;
                        if (id <= 5) {
                            ga = 1;
                        }
                        if (ga == 0) {
                            if (!(id >= 6 && id <= 0xb)) {
                                gb = 0;
                            }
                        }
                        if (gb == 0) {
                            if (!(id >= 0xc && id <= 0x11)) {
                                gc = 0;
                            }
                        }
                        if (gc == 0) {
                            if (!((id >= 0x12 && id <= 0x19) || id == 0x1c)) {
                                gd = 0;
                            }
                        }
                        if (gd == 0) {
                            if (!((id >= 0x8a && id <= 0x8f) || (id >= 0x90 && id <= 0x95) || (id >= 0x96 && id <= 0x9b) ||
                                  (id >= 0x9c && id <= 0xa3) || id == 0xa5)) {
                                ge = 0;
                            }
                        }
                        if (ge == 0) {
                            if (id != 0x1a) {
                                gf = 0;
                            }
                        }
                        if (gf == 0) {
                            if (id != 0xa4) {
                                gg = 0;
                            }
                        }
                        if (gg == 0) {
                            if (id != 0x1d) {
                                gh = 0;
                            }
                        }
                        if (gh != 0) {
                            if (k <= 1) {
                                if (func_ov003_02235518(p1, o) != 0) {
                                    flag1 = 1;
                                }
                            } else {
                                flag1 = 1;
                            }
                        }
                    }
                    count++;
                    break;
                case 2:
                    hh = 1;
                    hg = 1;
                    hf = 1;
                    he = 1;
                    hd = 1;
                    hc = 1;
                    hb = 1;
                    ha = 0;
                    id = *o;
                    if (id <= 5) {
                        ha = 1;
                    }
                    if (ha == 0) {
                        if (!(id >= 6 && id <= 0xb)) {
                            hb = 0;
                        }
                    }
                    if (hb == 0) {
                        if (!(id >= 0xc && id <= 0x11)) {
                            hc = 0;
                        }
                    }
                    if (hc == 0) {
                        if (!((id >= 0x12 && id <= 0x19) || id == 0x1c)) {
                            hd = 0;
                        }
                    }
                    if (hd == 0) {
                        if (!((id >= 0x8a && id <= 0x8f) || (id >= 0x90 && id <= 0x95) || (id >= 0x96 && id <= 0x9b) ||
                              (id >= 0x9c && id <= 0xa3) || id == 0xa5)) {
                            he = 0;
                        }
                    }
                    if (he == 0) {
                        if (id != 0x1a) {
                            hf = 0;
                        }
                    }
                    if (hf == 0) {
                        if (id != 0xa4) {
                            hg = 0;
                        }
                    }
                    if (hg == 0) {
                        if (id != 0x1d) {
                            hh = 0;
                        }
                    }
                    if (hh == 0) {
                        break;
                    }
                    if (p1 == 0xf) {
                        if (func_ov003_02235518(p1, o) == 0) {
                            break;
                        }
                        count++;
                        break;
                    }
                    count++;
                    break;
                case 9:
                    if (func_02031acc(wx, wy) != 0) {
                        break;
                    }
                    if (*o != 0xfff1) {
                        break;
                    }
                    count++;
                    break;
                case 8:
                    id = *o;
                    if (id == 0x1b) {
                        flag1 = 1;
                        count++;
                        break;
                    }
                    if (id != 0xfff1) {
                        break;
                    }
                    count++;
                    break;
                case 0:
                    if (*o != 0xfff1) {
                        break;
                    }
                    count++;
                    break;
                case 11:
                    if (((*rowp << i) & 1) != 0) {
                        break;
                    }
                    count++;
                    break;
                case 10:
                    f1 = 0;
                    id = *o;
                    if (id >= 0xe3 && id <= 0xe7) {
                        f1 = 1;
                    }
                    if (f1 == 0) {
                        break;
                    }
                    count++;
                    break;
                case 12:
                    if (func_ov003_0222c71c(o) == 0) {
                        break;
                    }
                    count++;
                    break;
                case 14:
                    if (func_ov003_0222c71c(o) == 0) {
                        if (func_ov003_0222c704(o) == 0) {
                            break;
                        }
                    }
                    count++;
                    break;
                case 15:
                    if (func_ov003_0222c71c(o) == 0) {
                        if (func_ov003_0222c704(o) == 0) {
                            if (func_ov003_0222c6f0(o) == 0) {
                                break;
                            }
                        }
                    }
                    count++;
                    break;
                case 13:
                    if (func_ov003_0222c6f0(o) == 0) {
                        break;
                    }
                    count++;
                    break;
                case 5:
                    if (func_02031b5c(wx, wy) != 2) {
                        break;
                    }
                    count++;
                    break;
                case 3:
                    break;
            }
        L_next:
            if (count == n0) {
                *rowp = *rowp | (1 << i);
            }
        L_inc:
            i++;
        } while (i < 0x10);
        j++;
    } while (j < 0x10);
    if (p5 == 1 || p5 == 8 || (p5 == 7 && p1 == 0x33)) {
        if (count > 0 && flag1 != 0) {
            func_ov003_0222c68c(count, base, p2, p3);
            return 1;
        }
    } else if (count > 0) {
        func_ov003_0222c68c(count, base, p2, p3);
        return 1;
    }
    return 0;
}
