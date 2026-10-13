/* func_020bbb20 @ 0x020bbb20, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020bba14(int arg);
extern void func_02002bd0(int a, int b, int c, int d, int e);
extern unsigned char data_020d22b4[];
struct UnkStruct_020bbb20 {
    int unk_00;
    int pad_04;
    int unk_08;
};
struct UnkStruct_020bbb20_2 {
    unsigned char pad_00[0x24];
    int unk_24;
    int unk_28;
};
extern struct UnkStruct_020bbb20 data_021f8b14;
extern struct UnkStruct_020bbb20_2 data_021f8ab0;

void func_020bbb20(int arg)
{
    struct UnkStruct_020bbb20 *p = &data_021f8b14;
    func_020bba14(arg);
    if (data_021f8ab0.unk_28 != data_021f8ab0.unk_24) {
        func_02002bd0(p->unk_08, data_020d22b4[arg], 1, 1, 1);
    } else {
        func_02002bd0(p->unk_00, data_020d22b4[arg], 1, 1, 1);
    }
}
