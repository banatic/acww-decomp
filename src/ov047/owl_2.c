/* owl_2: 2 functions, module ov047
 * mwccarm 1.2/base -O4,s
 * func_ov047_022619f0 @ 0x022619f0, 0x34 bytes, Thumb
 * func_ov047_022619b4 @ 0x022619b4, 0x3c bytes, Thumb
 */

struct UnkStruct_022619b4 {
    char pad_00[0x564];
    char unk_564;
    char pad_565[0x1cb];
    unsigned short unk_730;
};

extern unsigned short data_020c80f8;
extern int func_02019d0c(char *a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k);
extern int func_02019e00(void *);
extern int func_02019de8(void *);
extern void func_ov047_022624f4(void *, int);

int func_ov047_022619f0(char *ptr)
{
    func_02019d0c(ptr + 0x564, 0xa, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}

int func_ov047_022619b4(struct UnkStruct_022619b4 *arg)
{
    if (func_02019e00(&arg->unk_564) == 10 && func_02019de8(&arg->unk_564) != 0) {
        arg->unk_730 = 0x18;
        func_ov047_022624f4(arg, 0);
    }
    return 1;
}
