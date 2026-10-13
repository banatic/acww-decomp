/* func_02093820 @ 0x02093820, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02093820 {
    unsigned char pad_00[0x54];
    int unk_54;
};

struct UnkStruct_02093820_2 {
    unsigned char pad_00[0xc];
    struct UnkStruct_02093820 *unk_0C;
};

extern void func_02094c38(struct UnkStruct_02093820_2 *outer, int a, int b);

void func_02093820(struct UnkStruct_02093820_2 *outer)
{
    func_02094c38(outer, 0, 0);
    outer->unk_0C->unk_54 = 0xccd;
}
