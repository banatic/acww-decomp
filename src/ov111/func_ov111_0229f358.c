/* func_ov111_0229f358 @ 0x0229f358, 0x54 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40[];
extern int func_ov111_0229fb8c(void *param, int arg);
extern void func_ov095_0229bf3c(void *ptr);
extern void func_ov002_02208098(void *param, int arg);
extern void func_ov111_022a09f8(void *param, int a, int b);

typedef struct UnkStruct_0229f358 {
    unsigned char unk_00[0x8d];
    unsigned char unk_8D;
    unsigned char pad_8E[0x0a];
    unsigned char unk_98;
    unsigned char pad_99[0x13];
    void *unk_AC;
} UnkStruct_0229f358;

int func_ov111_0229f358(UnkStruct_0229f358 *param)
{
    if (!(data_021fbe40[1] & 2)) {
        return 0;
    }
    if (func_ov111_0229fb8c(param, 0) != 0) {
        func_ov095_0229bf3c(&param->unk_AC);
        param->unk_98 = param->unk_8D;
        func_ov002_02208098(param, 8);
    } else {
        func_ov111_022a09f8(param, 7, 0);
    }
    return 1;
}
