/* func_0206d500 @ 0x0206d500, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0206d500 {
    unsigned char pad_00[4];
    unsigned int unk_04;
    unsigned char pad_08[0x28];
    unsigned int unk_30;
    unsigned char pad_34[0x14];
    unsigned int unk_48;
    unsigned int unk_4C;
};

extern void func_020a8e8c(unsigned int);
extern void func_020a9318(struct UnkStruct_0206d500 *);

void func_0206d500(struct UnkStruct_0206d500 *param)
{
    if (param->unk_30) {
        func_020a8e8c(param->unk_30);
    }
    if (param->unk_04 == param->unk_48) {
        param->unk_48 = 0;
        func_020a9318(param);
    }
    if (param->unk_04 == param->unk_4C) {
        param->unk_4C = 0;
        func_020a9318(param);
    }
}
