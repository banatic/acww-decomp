/* func_020efa30 @ 0x020efa30, 0xc bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020efa30 {
    char pad_00[4];
    unsigned short unk_04;
    char pad_06[4];
    unsigned char unk_0A;
};
void func_020efa30(struct UnkStruct_020efa30 *p, unsigned char b, unsigned short h)
{
    p->unk_0A = b;
    p->unk_04 = h;
}
