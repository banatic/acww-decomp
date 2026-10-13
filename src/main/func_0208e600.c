/* func_0208e600 @ 0x0208e600, 0x1f0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x0c];
    u8 unk_0C[0x20 - 0x0c];
    int unk_20;
    int unk_24;
    int unk_28;
    u8 unk_2C[0x40 - 0x2c];
    int unk_40;
    u8 pad_44[0x48 - 0x44];
    u8 unk_48;
    u8 unk_49;
    u8 unk_4A;
} UnkStruct_0208e600;

extern void *func_0208a1d0(void *p);
extern short func_0208a1b0(void *p, int n);
extern short func_0208a198(void *p, int n);
extern int func_0208aef0(UnkStruct_0208e600 *s);
extern int func_0208aeec(UnkStruct_0208e600 *s);
extern void func_02088df8(int m, void *h, int a, int b, int c, int d, int e, int g, int i, int j, int k, int l);

void func_0208e600(UnkStruct_0208e600 *self)
{
    // DECLS
    int t30;
    void *x;
    int t2c;
    unsigned int ax;
    int py;
    int dx;
    int bx;
    int t7;
    int t34;
    int px;
    int cx;
    void *y;
    // ENDDECLS

    if (self->unk_40 == 0) {
        return;
    }

    x = func_0208a1d0(self->unk_0C);
    if (self->unk_49 != 0) {
        y = func_0208a1d0(self->unk_2C);
    } else {
        y = 0;
    }

    t7 = func_0208a1b0(self->unk_0C, -1);
    t2c = func_0208a198(self->unk_0C, -1);
    t30 = func_0208a1b0(self->unk_2C, -1);
    t34 = func_0208a198(self->unk_2C, -1);

    px = (int) ((char *) 0 + (self->unk_20 + func_0208aef0(self)));
    py = (int) ((char *) 0 + (self->unk_24 + func_0208aeec(self)));

    ax = px + t7;
    bx = py + t2c;
    cx = px + t30;
    dx = py + t34;

    if (self->unk_48 != 0) {
        func_02088df8(0, x, ax, bx, -1, self->unk_28, 0x1000, 0x1000, 0, -1, 0, 0);
        if (y != 0) {
            func_02088df8(0, y, cx, (py + t34), -1, self->unk_28, 0x1000, 0x1000, 0, -1, 0, 0);
        }
        if (self->unk_4A != 0) {
            func_02088df8(0, x, ax, bx, -1, self->unk_28, 0x1000, 0x1000, 0, 2, 0, 0);
            if (y != 0) {
                func_02088df8(0, y, cx, dx, -1, self->unk_28, 0x1000, 0x1000, 0, 2, 0, 0);
            }
        }
    } else {
        func_02088df8(1, x, ax, bx, -1, self->unk_28, 0x1000, 0x1000, 0, -1, 0, 0);
        if (y != 0) {
            func_02088df8(1, y, cx, dx, -1, self->unk_28, 0x1000, 0x1000, 0, -1, 0, 0);
        }
        if (self->unk_4A != 0) {
            func_02088df8(1, x, ax, bx, -1, self->unk_28, 0x1000, 0x1000, 0, 2, 0, 0);
            if (y != 0) {
                func_02088df8(1, y, cx, dx, -1, self->unk_28, 0x1000, 0x1000, 0, 2, 0, 0);
            }
        }
    }
}
