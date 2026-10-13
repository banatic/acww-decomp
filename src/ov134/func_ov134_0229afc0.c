/* func_ov134_0229afc0 @ 0x0229afc0, 0x2c bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229afc0 {
    char pad_00[0x94];
    unsigned short unk_94;
};

extern int func_ov134_0229aed4(struct UnkStruct_0229afc0 *self, int p1, int p2, int value);
extern void func_ov134_0229accc(struct UnkStruct_0229afc0 *self, int value);

void func_ov134_0229afc0(struct UnkStruct_0229afc0 *self, int p1, int p2)
{
    int ret;

    ret = func_ov134_0229aed4(self, p1, p2, self->unk_94);
    if (ret != 0) {
        func_ov134_0229accc(self, (ret * 0x2d0) >> 16);
    }
}
