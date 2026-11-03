/* town_list_states_4: 4 functions, module ov141
 * mwccarm 1.2/base -O4,s
 * func_ov141_0229ae80 @ 0x0229ae80, 0x54 bytes, Thumb
 * func_ov141_0229ae60 @ 0x0229ae60, 0x1e bytes, Thumb
 * func_ov141_0229ae44 @ 0x0229ae44, 0x1a bytes, Thumb
 * func_ov141_0229ad00 @ 0x0229ad00, 0x144 bytes, Thumb
 */

#include "types.h"

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

extern void *func_ov002_02207f80(unsigned int size);
extern void *func_ov002_0220830c(void *ptr);
extern void *func_ov139_02299b54(void *ptr);
extern void *func_ov002_02209ccc(void *ptr);
extern void *func_ov002_0220b008(void *ptr);
extern void *func_020b9cfc(void *ptr);
extern char data_ov141_0229af48;
extern void func_ov141_0229a9b0(void *);
extern unsigned char *func_ov002_022080a0(void *, unsigned char);
extern int func_020ee45c(void *argument0);
extern void func_ov092_0229929c(void *argument0);
extern void func_ov141_0229a984(int);
extern int func_0206fe54(void);
extern void func_ov002_02209eb8(void *ptr);
extern int func_ov141_02299f7c(void *self, int a);
extern void func_ov002_0220ad18(void *ptr, int val);
extern int func_ov139_022995d8(void *ptr, int idx);
extern void func_02088df8(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k, int l);
extern void func_ov139_02299a68(void *self, int a, int b);

void *func_ov141_0229ae80(void)
{
    void *p;

    p = func_ov002_02207f80(0x1A90);
    if (p != 0) {
        func_ov002_0220830c(p);
        *(void **) p = &data_ov141_0229af48;
        func_ov139_02299b54((char *) p + 0x94);
        func_ov002_02209ccc((char *) p + 0xA38);
        func_ov002_0220b008((char *) p + 0xA9C);
        func_020b9cfc((char *) p + 0xC68);
    }
    return p;
}

int func_ov141_0229ae60(void *p)
{
    func_ov141_0229a9b0(p);
    ((unsigned char *) p)[0x8c] = 0;
    func_ov002_022080a0(p, 0);
    return 1;
}

int func_ov141_0229ae44(int arg)
{

    func_ov092_0229929c((void *) func_020ee45c((void *) arg));
    func_ov141_0229a984(arg);
    return 1;
}

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
