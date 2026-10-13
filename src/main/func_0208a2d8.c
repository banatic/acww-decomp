/* func_0208a2d8 @ 0x0208a2d8, 0x114 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0208a2d8 {
    u8 pad_00[0xc];
    u8 unk_0C[0x14];
    u8 unk_20[0x14];
    int unk_34;
    int unk_38;
    int unk_3C;
    u8 unk_40;
    u8 unk_41;
} UnkStruct_0208a2d8;

extern int func_0208a1d0(void *);
extern int func_0208a1b0(void *, int);
extern int func_0208a198(void *, int);
extern int func_0208aef0(UnkStruct_0208a2d8 *);
extern int func_0208aeec(UnkStruct_0208a2d8 *);
extern void func_02088df8(int, int, int, int, int, int, int, int, int, int, int, int);

void func_0208a2d8(UnkStruct_0208a2d8 *p)
{
    int v20;
    int v24;
    int t;
    int v28;
    int v2c;
    int v30;
    int x;
    int y;

    if (!p->unk_34) {
        return;
    }
    v20 = func_0208a1d0(&p->unk_0C[0]);
    v24 = func_0208a1d0(&p->unk_20[0]);
    t = func_0208a1b0(&p->unk_0C[0], -1);
    v28 = func_0208a198(&p->unk_0C[0], -1);
    v2c = func_0208a1b0(&p->unk_20[0], -1);
    v30 = func_0208a198(&p->unk_20[0], -1);
    x = p->unk_38 + func_0208aef0(p);
    y = p->unk_3C + func_0208aeec(p);
    if (p->unk_41) {
        func_02088df8(0, v20, x + t, y + v28, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
        func_02088df8(0, v24, x + v2c, y + v30, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
    } else {
        func_02088df8(1, v20, x + t, y + v28, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
        func_02088df8(1, v24, x + v2c, y + v30, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
    }
}
