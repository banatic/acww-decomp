/* func_02014d8c @ 0x02014d8c, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019e00(unsigned int a);
extern int func_02019de8(unsigned int a);
extern void func_02068434(unsigned int a);

struct UnkStruct_02014d8c {
    char pad_00[0x40];
    unsigned int unk_40;
    char pad_44[8];
    unsigned int unk_4C;
    char pad_50[92];
    char unk_AC;
};

int func_02014d8c(struct UnkStruct_02014d8c *param)
{
    int result = 0;
    if (param->unk_4C != 0 && param->unk_40 != 0) {
        if (func_02019e00(param->unk_4C + 0x564) == 0x12) {
            if (func_02019de8(param->unk_4C + 0x564) != 0) {
                func_02068434(param->unk_40);
                param->unk_AC = 2;
                result = 1;
            }
        }
    }
    return result;
}
