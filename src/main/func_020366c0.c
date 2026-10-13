/* func_020366c0 @ 0x020366c0, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020366c0 {
    char pad_00[10];
    unsigned short unk_0A;
};

extern void func_02035638(unsigned int value);

void func_020366c0(struct UnkStruct_020366c0 *p)
{
    if (p->unk_0A != 0xffff) {
        func_02035638(p->unk_0A);
        p->unk_0A = 0xffff;
    }
}
