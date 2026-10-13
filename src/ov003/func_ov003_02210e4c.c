/* func_ov003_02210e4c @ 0x02210e4c, 0x6c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02210e4c {
    char pad_00[0x2d8];
    int unk_2D8;
    char pad_2DC[0x428];
    int unk_704;
    char pad_708[0x128];
    int array[3];
};

extern void func_02010f5c(struct UnkStruct_02210e4c *);
extern int _s32_div_f(int, int);
extern void func_0200f268(struct UnkStruct_02210e4c *, int);
extern void func_0200f650(struct UnkStruct_02210e4c *, int);

void func_ov003_02210e4c(struct UnkStruct_02210e4c *param)
{
    int r4;
    int shifted;
    int result;

    func_02010f5c(param);
    if (param->unk_704 == 0x50) {
        shifted = (int) (((unsigned int) ((param->unk_2D8 >> 12) << 16)) >> 4);
        result = _s32_div_f(shifted, 6);
        r4 = 0x1000 - result;
        if (r4 < 0) {
            r4 = 0;
            func_0200f268(param, 13);
        }
    } else {
        r4 = 0;
    }
    param->array[0] = r4;
    param->array[1] = r4;
    param->array[2] = r4;
    func_0200f650(param, r4);
}
