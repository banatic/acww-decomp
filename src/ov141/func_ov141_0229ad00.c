/* func_ov141_0229ad00 @ 0x0229ad00, 0x144 bytes, Thumb, module ov141
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0206fe54(void);
extern void func_ov002_02209eb8(void *ptr);
extern int func_ov141_02299f7c(void *self, int a);
extern void func_ov002_0220ad18(void *ptr, int val);
extern int func_ov139_022995d8(void *ptr, int idx);
extern void func_02088df8(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k, int l);
extern void func_ov139_02299a68(void *self, int a, int b);

typedef struct {
    u8 pad_00[0x94];
    u8 sub94;
    u8 pad_95[0x9a3];
    u8 suba38;
    u8 pad_A39[0x63];
    u8 suba9c;
    u8 pad_A9D[0x7cb];
    s32 unk_1268;
    s32 unk_126C;
    s32 unk_1270;
    s32 unk_1274;
    s32 unk_1278;
} UnkStruct_0229ad00;

int func_ov141_0229ad00(UnkStruct_0229ad00 *self)
{
    int r4;
    int r6, r7;
    int c, d;

    if (func_0206fe54()) {
        func_ov002_02209eb8(&self->suba38);
    }
    if (func_ov141_02299f7c(self, 1) == 0) {
        return 0;
    }

    func_ov002_0220ad18(&self->suba9c, self->unk_126C);

    r4 = self->unk_1268 + 0x60;
    r6 = func_ov139_022995d8(&self->sub94, 0);
    r7 = func_ov139_022995d8(&self->sub94, 1);
    c = func_ov139_022995d8(&self->sub94, 2);
    d = func_ov139_022995d8(&self->sub94, 3);

    if (self->unk_1270 != -1) {
        func_02088df8(1, r7, 0x80, r4 + (self->unk_1270 << 4), -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
    }
    func_02088df8(1, r6, 0x80, r4, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
    func_02088df8(1, c, 0x80, r4, self->unk_1278, 2, 0x1000, 0x1000, 0, -1, 0, 0);
    func_02088df8(1, d, 0x80, r4, self->unk_1274, 2, 0x1000, 0x1000, 0, -1, 0, 0);
    func_ov139_02299a68(&self->sub94, 0, self->unk_1268);
    return 1;
}
