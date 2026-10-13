/* func_02036ab4 @ 0x02036ab4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02035638(unsigned short);

struct UnkStruct_02036ab4 {
    unsigned char pad_00[0xe];
    unsigned short unk_0E;
};

void func_02036ab4(struct UnkStruct_02036ab4 *p)
{
    if (p->unk_0E != 0xffff) {
        func_02035638(p->unk_0E);
        p->unk_0E = 0xffff;
    }
}
