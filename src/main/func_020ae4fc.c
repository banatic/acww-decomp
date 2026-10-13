/* func_020ae4fc @ 0x020ae4fc, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020ae4fc {
    unsigned char pad_00[5];
    unsigned char flags;
};

void func_020ae4fc(struct UnkStruct_020ae4fc *p, int shift)
{
    p->flags &= ~(1 << (shift & 3));
}
