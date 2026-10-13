/* func_02083dcc @ 0x02083dcc, 0x174 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

typedef struct {
    int a;
    int b;
} Pair;

typedef struct {
    unsigned int a;
    unsigned int b;
} UnkStruct_02083dcc;
typedef struct {
    int unk_00;
    UnkStruct_02083dcc s;
} Map;

extern u32 data_021d212c;
extern Pair data_021d222c[];
extern int data_021d2230[];
extern u8 data_020e54a8;
extern Map *data_021c80bc;

extern int func_02037d64(void *p, int m);
extern int func_02037d80(void *p, int m);
extern void func_0204f800(int *sx, int *sy, int cx, int cy, int e, int f);
extern int func_02031a48(int x, int y);
extern int func_020644cc(int n);
extern void func_0204f794(int a, int x, int y);

int func_02083dcc(int unused, int arg)
{
    // DECLS
    Pair *q;
    Pair *e;
    unsigned int ok;
    Map *m;
    UnkStruct_02083dcc *sp2;
    void *p;
    int w;
    int h;
    int n;
    int cx;
    int cy;
    int x0;
    int x1;
    int y1;
    int x;
    int y;
    // ENDDECLS
    int sx;
    int sy;

    if ((data_021d212c & 1) == 0) {
        q = data_021d222c;
        do {
            q->a = 0;
            q->b = 0;
            q++;
        } while (q != data_021d222c + 0x20);
        data_021d212c = data_021d212c | 1;
    }
    if (data_020e54a8 != 0) {
        ok = 0;
    } else {
        ok = 1;
    }
    if (ok != 0) {
        m = data_021c80bc;
        if (m == 0) {
            return 0;
        }
        sp2 = &m->s;
        w = (int) m->s.a;
        h = (int) sp2->b;
        y = n = 0;
        for (cy = 0; cy < h; cy++) {
            for (cx = 0; cx < w; cx++) {
                if (cx < m->s.a && cy < m->s.b && m->unk_00 != 0) {
                    p = (void *) ((char *) m->unk_00 + (cx + cy * m->s.a) * 0x28);
                } else {
                    p = 0;
                }
                if (p != 0 && func_02037d64(p, 0x7f000) != 0 && func_02037d80(p, 8) != 0) {
                    sx = 0;
                    sy = 0;
                    func_0204f800(&sx, &sy, cx, cy, 0, 0);
                    x1 = sx;
                    x1 = x1 + 0x10;
                    y = sy;
                    y1 = sy;
                    y1 = y1 + 0x10;
                    for (; y < y1; y++) {
                        for (x = sx; x < x1; x++) {
                            if (func_02031a48(x, y) != 0) {
                                e = &data_021d222c[n];
                                data_021d222c[n].a = x;
                                e->b = y;
                                n++;
                            }
                            if (n >= 0x20) {
                                break;
                            }
                        }
                        if (n >= 0x20) {
                            break;
                        }
                    }
                    if (n >= 0x20) {
                        break;
                    }
                }
            }
            if (n >= 0x20) {
                break;
            }
        }
        if (n > 0) {
            n = func_020644cc(n) * 8;
            func_0204f794(arg, *(int *) ((char *) data_021d222c + n), *(int *) ((char *) data_021d2230 + n));
            return 1;
        }
    }
    return 0;
}
