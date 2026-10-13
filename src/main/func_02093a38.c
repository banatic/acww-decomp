/* func_02093a38 @ 0x02093a38, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02093a38 UnkStruct_02093a38;
struct UnkStruct_02093a38 {
    char pad_00[0x50];
    unsigned int unk_50;
};

typedef struct UnkStruct_02093a38_2 UnkStruct_02093a38_2;
struct UnkStruct_02093a38_2 {
    char pad_00[0xc];
    UnkStruct_02093a38 *unk_0C;
};

extern void func_02094bc0(UnkStruct_02093a38_2 *a);

void func_02093a38(UnkStruct_02093a38_2 *a)
{
    func_02094bc0(a);
    a->unk_0C->unk_50 = 0x99a;
}
