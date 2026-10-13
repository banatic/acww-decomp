/* func_020af2d0 @ 0x020af2d0, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);

struct UnkA {
    char pad_00[0x4e];
    unsigned char unk_4E;
    unsigned char unk_4F;
    unsigned char unk_50;
    unsigned char unk_51;
};

int func_020af2d0(struct UnkA *a, const unsigned char *b)
{
    unsigned char buf[8];

    MI_CpuCopy8(b, buf, 8);
    if (a->unk_50 != buf[5] || a->unk_4F != buf[4] || a->unk_4E != buf[3] || a->unk_51 != 0) {
        return 1;
    }
    return 0;
}
