/* func_ov068_02274314 @ 0x02274314, 0x20 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov068_022740f8(void *self, int arg);

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

void func_ov068_02274314(ThisType *self)
{
    self->unk_40->unk_14 = 0;
    *(short *) (self->unk_B4 + 0x748) = 0x2d;
    func_ov068_022740f8(self, 2);
}
