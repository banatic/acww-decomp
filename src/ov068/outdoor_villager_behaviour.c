/* outdoor_villager_behaviour: 4 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_0226cce4 @ 0x0226cce4, 0x4 bytes, Thumb
 * func_ov068_0226ccd8 @ 0x0226ccd8, 0xc bytes, Thumb
 * func_ov068_0226ccd0 @ 0x0226ccd0, 0x6 bytes, Thumb
 * func_ov068_0226ccb0 @ 0x0226ccb0, 0x20 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x10];
    void *unk_10;
} UnkStruct_0226ccd8;

typedef struct {
    unsigned char pad_00[24];
    unsigned long unk_18;
} UnkStruct_0226ccd0;

struct UnkStruct_0226ccb0 {
    char pad_00[0x18];
    int unk_18;
};

extern void func_ov068_0226cce8(struct UnkStruct_0226ccb0 *, void *, int);

void func_ov068_0226cce4(int *p0, int p1)
{
    p0[6] = p1;
}

void func_ov068_0226ccd8(UnkStruct_0226ccd8 *self)
{
    func_ov068_0226cce4((int *) self, (int) self->unk_10);
}

void func_ov068_0226ccd0(UnkStruct_0226ccd0 *p)
{
    p->unk_18 = 24;
}

int func_ov068_0226ccb0(struct UnkStruct_0226ccb0 *self, void *b)
{
    int r = 0;
    if (self->unk_18 < 0x18) {
        func_ov068_0226cce8(self, b, self->unk_18);
        func_ov068_0226ccd0((UnkStruct_0226ccd0 *) self);
        r = 1;
    }
    return r;
}
