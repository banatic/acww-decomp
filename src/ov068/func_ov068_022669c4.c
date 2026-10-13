/* func_ov068_022669c4 @ 0x022669c4, 0x3c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022669c4;

extern void func_ov068_02266be4(struct UnkStruct_022669c4 *obj, int a1, int a2, int a3, int a4, int a5, int a6, int a7,
                                int a8);
extern int data_020c814c;

struct UnkStruct_022669c4 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    short unk_14;
};

void func_ov068_022669c4(struct UnkStruct_022669c4 *obj, int param1, int param2, int param3, int param4)
{
    obj->unk_0C = param2;
    obj->unk_10 = param3;
    func_ov068_02266be4(obj, param1, 3, 0, 0, param4, 4, data_020c814c, 1);
    obj->unk_04 = 1;
    obj->unk_14 = 0;
}
