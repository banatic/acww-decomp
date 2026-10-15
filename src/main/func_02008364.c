/* func_02008364 @ 0x02008364, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020109fc(int a, int b, unsigned short c, unsigned short d);
extern void func_0200eebc(int a);

struct UnkStruct_02008364 {
    char pad_00[0xc];
    unsigned short unk_0C;
};

void func_02008364(int a, struct UnkStruct_02008364 *b, int previous)
{
    unsigned short val = b->unk_0C;
    func_020109fc(a, 0, val, val);
    func_0200eebc(a);
}
