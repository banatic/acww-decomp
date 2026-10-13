/* func_02068b88 @ 0x02068b88, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020045cc(int param);

struct UnkStruct_02068b88 {
    char pad_00[0x20];
    int unk_20;
    int unk_24;
};

void func_02068b88(struct UnkStruct_02068b88 *param0, int param1)
{
    if (param0->unk_20 == 5 && param0->unk_24 != 5 && param0->unk_24 != param1) {
        func_020045cc(param1);
        param0->unk_24 = param1;
    }
}
