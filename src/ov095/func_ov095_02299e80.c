/* func_ov095_02299e80 @ 0x02299e80, 0xbc bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02299e80 {
    char pad_00[0x28];
    int unk_28;
    int unk_2C;
} UnkStruct_02299e80;

extern int func_ov002_022088bc(void *p);
extern int func_ov002_022088cc(void *p);
extern int func_ov002_022088ac(void *p);
extern int func_ov002_0220889c(void *p);
extern int func_ov090_02298f84(int a);
extern void func_ov095_022999a8(UnkStruct_02299e80 *self, int n);
extern int func_ov095_0229cdf0(UnkStruct_02299e80 *self, int v);

int func_ov095_02299e80(UnkStruct_02299e80 *self, void *pad)
{
    int v;

    v = self->unk_28;
    if (v == 0xf7) {
        if (func_ov002_022088bc(pad) != 0) {
            self->unk_28 = 0x10a;
        } else if (func_ov002_022088cc(pad) != 0) {
            self->unk_28 = func_ov090_02298f84(self->unk_2C) + 0xfb;
        } else if (func_ov002_022088ac(pad) != 0) {
            func_ov095_022999a8(self, 0x10);
        }
        return 1;
    }
    if (func_ov095_0229cdf0(self, v) == 0) {
        goto ret0;
    }
    if (func_ov002_022088bc(pad) != 0) {
        if (self->unk_28 >= 0x101) {
            self->unk_28 = 0xf7;
        } else {
            func_ov095_022999a8(self, 0x10);
        }
        return 1;
    }
    if (func_ov002_0220889c(pad) != 0) {
        v = self->unk_28;
        if (v < 0x102) {
            self->unk_28 = v + 1;
        }
    } else if (func_ov002_022088ac(pad) != 0) {
        v = self->unk_28;
        if (v > 0xfb) {
            self->unk_28 = v - 1;
        }
    }
    return 1;
ret0:
    return 0;
}
