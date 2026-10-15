/* func_ov112_022a1600 @ 0x022a1600, 0x64 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022a1600 {
    char pad_00[0xA0];
    int unk_A0;
    char pad_A4[4];
    int unk_A8;
};

extern void func_ov002_02207f20(struct UnkStruct_022a1600 *p, int a, int b, int c, int d);
extern void func_02002708(int a);
extern void func_ov002_02207e80(struct UnkStruct_022a1600 *p, int a, int b, int c);
extern void func_ov002_02208090(struct UnkStruct_022a1600 *p, int a);
extern int func_ov002_02207f60(struct UnkStruct_022a1600 *p);
extern void func_ov112_0229fe60(struct UnkStruct_022a1600 *p, int a);
extern int func_ov002_0220acc4(void *p);

void func_ov112_022a1600(struct UnkStruct_022a1600 *param)
{
    func_ov002_02207f20(param, 8, 0, 0, 0x30);
    func_02002708(6);
    func_ov002_02207e80(param, 6, 0, 0);
    func_ov002_02208090(param, 9);
    param->unk_A0 = func_ov002_02207f60(param);
    param->unk_A8 = param->unk_A0;
    func_ov112_0229fe60(param, 1);
    func_ov002_0220acc4((char *) param + 0x427C);
}
