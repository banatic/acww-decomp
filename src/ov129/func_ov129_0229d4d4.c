/* func_ov129_0229d4d4 @ 0x0229d4d4, 0x2c bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229d4d4 {
    unsigned char pad_00[0xa0];
    int unk_A0;
};

extern int func_ov002_02207f48(void *a, int b);
extern void func_ov002_022080a0(void *a, int b);
extern void func_ov129_0229d360(void *a);
extern int func_ov002_02207f60(void *a);

void func_ov129_0229d4d4(struct UnkStruct_0229d4d4 *arg)
{
    if (func_ov002_02207f48(arg, 0)) {
        func_ov002_022080a0(arg, 2);
        func_ov129_0229d360(arg);
    }
    arg->unk_A0 = func_ov002_02207f60(arg);
}
