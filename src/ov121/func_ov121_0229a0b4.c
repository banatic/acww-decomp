/* func_ov121_0229a0b4 @ 0x0229a0b4, 0x2c bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f3c(void *);
extern int func_ov002_02209f14(void *);

struct UnkStruct_0229a0b4 {
    char pad_00[0xa4];
    unsigned short unk_A4;
    unsigned short unk_A6;
};

void func_ov121_0229a0b4(struct UnkStruct_0229a0b4 *self)
{
    int tmp;
    int tmp2;

    tmp = func_ov002_02209f3c((char *) self + 0x3a8);
    self->unk_A4 = (unsigned short) (tmp - 3);
    tmp2 = func_ov002_02209f14((char *) self + 0x3a8);
    self->unk_A6 = (unsigned short) (tmp2 + 9);
}
