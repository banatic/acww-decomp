/* func_02036b14 @ 0x02036b14, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02035610(int);

struct UnkStruct_02036b14 {
    char pad_00[8];
    unsigned short unk_08;
};

void func_02036b14(struct UnkStruct_02036b14 *p)
{
    if (p->unk_08 != 0xffff) {
        func_02035610(p->unk_08);
        p->unk_08 = 0xffff;
    }
}
