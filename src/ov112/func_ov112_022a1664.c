/* func_ov112_022a1664 @ 0x022a1664, 0x26 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xA8];
    int unk_A8;
} UnkStruct_022a1664;

extern int func_ov002_02207f3c(UnkStruct_022a1664 *param, int x);
extern void func_ov002_02208090(UnkStruct_022a1664 *param, int y);
extern int func_ov002_02207f60(UnkStruct_022a1664 *param);

void func_ov112_022a1664(UnkStruct_022a1664 *param)
{
    if (func_ov002_02207f3c(param, 0) != 0) {
        func_ov002_02208090(param, 8);
    }
    param->unk_A8 = func_ov002_02207f60(param);
}
