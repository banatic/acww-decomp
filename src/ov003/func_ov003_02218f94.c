/* func_ov003_02218f94 @ 0x02218f94, 0x16 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_020109a0(int, int, unsigned short, int);

struct UnkStruct_02218f94 {
    unsigned char pad_00[12];
    unsigned short unk_0C;
};

int func_ov003_02218f94(int a, struct UnkStruct_02218f94 *b)
{
    return func_020109a0(a, 0x9a, b->unk_0C, 0);
}
