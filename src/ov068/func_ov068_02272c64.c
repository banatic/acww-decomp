/* func_ov068_02272c64 @ 0x02272c64, 0x4c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov068_02272cb0(void *self);
extern void func_ov068_02272c54(void *self);
extern void func_02091278(unsigned int, void *, int, int);

struct UnkStruct_02272c64 {
    unsigned char pad_00[0x1e0];
    unsigned int unk_1E0;
    unsigned char pad_1E4[0x2cc - 0x1e4];
    unsigned int unk_2CC;
    unsigned char pad_2D0[0x2e0 - 0x2d0];
    unsigned int unk_2E0;
};

void func_ov068_02272c64(struct UnkStruct_02272c64 *self)
{
    unsigned int val;
    val = (self->unk_1E0 << 4) >> 16;
    if (val < 0x2d || val > 0x31) {
        return;
    }
    if (val == 0x2d) {
        func_ov068_02272cb0(self);
    }
    func_02091278(self->unk_2E0, &self->unk_2CC, 0, 0);
    if (val == 0x31) {
        func_ov068_02272c54(self);
    }
}
