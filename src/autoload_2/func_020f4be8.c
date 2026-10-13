/* func_020f4be8 @ 0x020f4be8, 0x40 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020f4be8 {
    unsigned char pad_00[8];
    unsigned short unk_08;
    unsigned char flags;
};

void func_020f4be8(struct UnkStruct_020f4be8 *p, unsigned short v)
{
    if (p->unk_08 != v) {
        p->flags |= 4;
    } else {
        p->flags &= ~4;
    }
    p->unk_08 = v;
    p->flags |= 2;
    p->flags |= 1;
}
