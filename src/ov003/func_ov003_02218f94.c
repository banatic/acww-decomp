/* func_ov003_02218f94 @ 0x02218f94, 0x16 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_020109a0(int, int b, int c, unsigned short d);

struct UnkStruct_02218f94 {
    unsigned char pad_00[12];
    unsigned short unk_0C;
};

void func_ov003_02218f94(int a, struct UnkStruct_02218f94 *b, int previous)
{
    func_020109a0(a, 0x9a, b->unk_0C, 0);
}
