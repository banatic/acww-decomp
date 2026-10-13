/* func_020ef968 @ 0x020ef968, 0x30 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020ef968 {
    int unk_00;
    unsigned short unk_04;
    unsigned short unk_06;
    unsigned char unk_08;
};

int func_020ef968(struct UnkStruct_020ef968 *p, unsigned char c1, unsigned short c2)
{
    if (p->unk_00 && p->unk_06 == c2 && p->unk_08 == c1) {
        return 1;
    }
    return 0;
}
