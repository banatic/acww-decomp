/* func_02037fe8 @ 0x02037fe8, 0x90 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xC0];
    int unk_C0;
    int unk_C4;
} UnkStruct_02037fe8;

extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned short data_021fbe40[];

extern void func_02038444(UnkStruct_02037fe8 *param, int field_c4, int arg2);
extern void func_0203859c(UnkStruct_02037fe8 *param);
extern void func_02038680(UnkStruct_02037fe8 *param, int field_c4);
extern void func_02037fd0(UnkStruct_02037fe8 *param);

void func_02037fe8(UnkStruct_02037fe8 *param)
{
    if (param->unk_C4 < 4) {
        func_02038444(param, param->unk_C4, 1);
        func_0203859c(param);
        func_02038680(param, param->unk_C4);
        param->unk_C4++;
    }
    param->unk_C0--;
    if (param->unk_C0 <= 0) {
        int cond1 = (data_021fbdd8 != 0) && (data_021fbddc != 0);
        int cond2 = (data_021fbe40[1] & 1) != 0;
        if (cond1 || cond2) {
            func_02037fd0(param);
        }
    }
}
