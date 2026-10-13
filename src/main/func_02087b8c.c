/* func_02087b8c @ 0x02087b8c, 0x174 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x;
    int y;
} Pair;
typedef struct {
    int a;
    int b;
} UnkStruct_02087b8c;
typedef struct {
    u8 pad_00[0xc];
    UnkStruct_02087b8c s;
} Map;
typedef struct {
    int x;
    int z;
    u8 unk_08;
} UnkStruct_02087b8c_2;
typedef struct {
    unsigned short bits[4];
} Buf;
typedef struct {
    int a, b, c;
} Out3;

extern Map *data_021c80bc;

extern void func_02087e20(UnkStruct_02087b8c_2 *self);
extern void func_0204f818(int *sx, int *sy, const int *b);
extern int func_02087d00(int *out, int (*cb)(int, int, Map *), int a, int b, int c, Map *m, Buf *buf, int n);
extern int func_020644cc(int n);
extern void func_0204f794(Out3 *o, int x, int y);
extern void func_02087e58(UnkStruct_02087b8c_2 *self, Out3 *o);
extern void func_02087e2c(UnkStruct_02087b8c_2 *self);
extern int func_02087dd8(int, int, Map *);
extern int func_02087dd0(int, int, Map *);

int func_02087b8c(UnkStruct_02087b8c_2 *self, const int *b, int c)
{
    Map *m;
    int ok1;
    long step;
    int ok2;
    int w;
    int h;
    int x;
    Pair *sel;
    UnkStruct_02087b8c *q;
    int y2;
    int y1;
    int x2;
    int sx;
    int sy;
    Pair pa;
    Pair pb;
    Buf buf1;
    Buf buf2;
    Out3 out;

    m = data_021c80bc;
    if (m == 0) {
        func_02087e20(self);
        return 0;
    }
    sel = 0;
    sx = 0;
    sy = 0;
    q = &m->s;
    w = q->a;
    h = q->b;
    pa.x = 0;
    pa.y = 0;
    pb.x = 0;
    pb.y = 0;
    if (c != 0) {
        step = -1;
    } else {
        step = 1;
    }
    func_0204f818(&sx, &sy, b);
    x = sx + (step * 8) - c;
    y1 = sy + 5;
    x2 = x;
    y2 = sy + 4;
    out.a = 0;
    out.b = 0;
    out.c = 0;
    while (y1 < h || (x2 >= 0 && x2 < w)) {
        if (y1 < h) {
            pa.y = y1;
            ok1 = func_02087d00(&pa.x, func_02087dd8, y1, x, sx, m, &buf1, 4);
            if (x > 0 && x < w - 1) {
                x = x + step;
            }
            y1++;
        }
        if (x2 >= 0 && x2 < w) {
            pb.x = x2;
            ok2 = func_02087d00(&pb.y, func_02087dd0, x2, sy, y2, m, &buf2, 4);
            x2 = x2 + step;
            if (y2 < h - 1) {
                y2++;
            }
        }
        if (ok1 != 0) {
            if (ok2 != 0) {
                if ((func_020644cc(0xa) & 1) != 0) {
                    sel = &pb;
                    break;
                }
            }
            sel = &pa;
            break;
        } else {
            if (ok2 != 0) {
                sel = &pb;
                break;
            }
        }
    }
    if (sel != 0) {
        func_0204f794(&out, sel->x, sel->y);
        func_02087e58(self, &out);
        self->unk_08 = (u8) ((self->unk_08 & ~0xc) | ((((u8) func_020644cc(4)) & 3) << 2));
        func_02087e2c(self);
        return 1;
    }
    func_02087e20(self);
    return 0;
}
