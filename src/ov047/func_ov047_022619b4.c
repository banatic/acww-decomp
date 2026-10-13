/* func_ov047_022619b4 @ 0x022619b4, 0x3c bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019e00(void *);
extern int func_02019de8(void *);
extern void func_ov047_022624f4(void *, int);

struct UnkStruct_022619b4 {
    char pad_00[0x564];
    char unk_564;
    char pad_565[0x1cb];
    unsigned short unk_730;
};

int func_ov047_022619b4(struct UnkStruct_022619b4 *arg)
{
    if (func_02019e00(&arg->unk_564) == 10 && func_02019de8(&arg->unk_564) != 0) {
        arg->unk_730 = 0x18;
        func_ov047_022624f4(arg, 0);
    }
    return 1;
}
