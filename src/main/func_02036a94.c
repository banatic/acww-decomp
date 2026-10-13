/* func_02036a94 @ 0x02036a94, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02035638(unsigned short value);

struct UnkStruct_02036a94 {
    char pad_00[0x10];
    unsigned short unk_10;
};

void func_02036a94(struct UnkStruct_02036a94 *s)
{
    if (s->unk_10 != 0xFFFF) {
        func_02035638(s->unk_10);
        s->unk_10 = 0xFFFF;
    }
}
