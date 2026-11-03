/* cafe_guest_4: 3 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_02274334 @ 0x02274334, 0x22 bytes, Thumb
 * func_ov068_02274314 @ 0x02274314, 0x20 bytes, Thumb
 * func_ov068_022742f4 @ 0x022742f4, 0x20 bytes, Thumb
 */

typedef struct {
    char pad_00[0x14];
    int unk_14;
} Sub40;

typedef struct {
    char pad_00[0x40];
    Sub40 *unk_40;
    char pad_44[0x70];
    char *unk_B4;
} ThisType;

struct inner_022743ec {
    char pad_00[0x730];
    int value;
};

struct outer_022743ec {
    char pad_00[0xb4];
    struct inner_022743ec *inner;
};

extern void func_020157c8(int, int, int);
extern int func_02015828(int, int);
extern void func_ov068_022740f8(int, int);
extern void func_ov068_02274238(void *self, int b);

void func_ov068_02274334(int r0)
{
    func_020157c8(r0, 13, 0);
    func_02015828(r0, 2);
    func_ov068_022740f8(r0, 1);
}

void func_ov068_02274314(ThisType *self)
{
    self->unk_40->unk_14 = 0;
    *(short *) (self->unk_B4 + 0x748) = 0x2d;
    func_ov068_022740f8((int) self, 2);
}

void func_ov068_022742f4(struct outer_022743ec *a, int b)
{
    if (a->inner->value == 7) {
        func_ov068_02274238(a, b);
    }
}
