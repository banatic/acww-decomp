/* func_ov112_022a17a8 @ 0x022a17a8, 0x60 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xa0];
    int unk_A0;
    char pad_A4[4];
    int unk_A8;
} UnkStruct_022a17a8;

extern void func_ov112_0229fe50(UnkStruct_022a17a8 *param, int arg);
extern void func_ov002_02207f04(UnkStruct_022a17a8 *param, int a, int b, int c, int d);
extern void func_ov002_02207e80(UnkStruct_022a17a8 *param, int a, int b, int c);
extern void func_ov002_02208090(UnkStruct_022a17a8 *param, int a);
extern int func_ov002_02207f60(UnkStruct_022a17a8 *param);
extern void func_ov112_0229fb7c(UnkStruct_022a17a8 *param, int arg);

void func_ov112_022a17a8(UnkStruct_022a17a8 *param)
{
    func_ov112_0229fe50(param, 0x40);
    func_ov002_02207f04(param, 8, 0, 0, 0x30);
    func_ov002_02207e80(param, 6, 0, 0);
    func_ov002_02208090(param, 3);
    param->unk_A0 = func_ov002_02207f60(param);
    param->unk_A8 = param->unk_A0;
    func_ov112_0229fb7c(param, 0);
    func_ov112_0229fe50(param, 0x80);
}
