/* func_ov129_0229b7ec @ 0x0229b7ec, 0x12 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229b7ec {
    unsigned char pad_00[0xA4];
    unsigned short unk_A4;
};

int func_ov129_0229b7ec(struct UnkStruct_0229b7ec *p, unsigned short mask)
{
    unsigned int combined = p->unk_A4 & mask;
    if (combined != 0) {
        return 1;
    }
    return 0;
}
