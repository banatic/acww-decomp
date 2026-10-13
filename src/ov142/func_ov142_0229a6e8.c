/* func_ov142_0229a6e8 @ 0x0229a6e8, 0x10 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229a6e8 {
    char pad_00[0xBC];
    unsigned char b;
};

short func_ov142_0229a6e8(struct UnkStruct_0229a6e8 *p)
{
    return *(short *) ((char *) p + p->b * 2 + 0xD6);
}
