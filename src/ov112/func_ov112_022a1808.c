/* func_ov112_022a1808 @ 0x022a1808, 0x94 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022a1808 {
    char pad_to_A0[0xA0];
    unsigned int unk_A0;
    unsigned int unk_A4;
    unsigned int unk_A8;
};

extern int func_ov112_0229fe70(struct UnkStruct_022a1808 *param, unsigned int arg);
extern int func_ov002_02207f48(struct UnkStruct_022a1808 *param, int arg);
extern void func_ov112_0229f11c(struct UnkStruct_022a1808 *param);
extern void func_ov112_0229f0ec(struct UnkStruct_022a1808 *param);
extern void func_ov112_0229fe50(struct UnkStruct_022a1808 *param, unsigned int arg);
extern void func_ov112_0229f6e4(struct UnkStruct_022a1808 *param);
extern unsigned char *func_ov002_022080a0(struct UnkStruct_022a1808 *param, unsigned char value);
extern int func_ov112_0229fefc(struct UnkStruct_022a1808 *param);
extern void func_ov112_0229fd20(struct UnkStruct_022a1808 *param);
extern void func_ov112_022a122c(struct UnkStruct_022a1808 *param);
extern void func_ov002_02207e80(struct UnkStruct_022a1808 *param, int a, int b, int c);
extern unsigned int func_ov002_02207f60(struct UnkStruct_022a1808 *param);

void func_ov112_022a1808(struct UnkStruct_022a1808 *param)
{
    if (func_ov112_0229fe70(param, 0x4000) != 0) {
        func_ov112_0229f11c(param);
        func_ov112_0229f0ec(param);
        func_ov112_0229fe50(param, 0x4000);
    }
    if (func_ov002_02207f48(param, 0) != 0) {
        func_ov112_0229f6e4(param);
        func_ov002_022080a0(param, 2);
        func_ov112_0229fefc(param);
        func_ov112_0229fd20(param);
        func_ov112_022a122c(param);
    }
    func_ov002_02207e80(param, 4, 0, -8);
    func_ov002_02207e80(param, 6, 0, 0);
    param->unk_A0 = func_ov002_02207f60(param);
    param->unk_A4 = param->unk_A0;
    param->unk_A8 = param->unk_A4;
}
