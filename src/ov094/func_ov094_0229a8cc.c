/* func_ov094_0229a8cc @ 0x0229a8cc, 0x8c bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_0229a4c0(int);
extern void MI_CpuCopy8(void *dst, const void *src, unsigned int size);
extern void func_020b9a18(char *a, char *b, char *c, int d, int e, int f, int g, int h);

typedef struct {
    unsigned int pad_00;
    union {
        struct {
            unsigned int low10 : 10;
            unsigned int : 2;
            unsigned int nibble : 4;
            unsigned int : 16;
        } bits;
        unsigned int raw;
    } unk_04;
} UnkStruct_0229a8cc;

void func_ov094_0229a8cc(char *r0, UnkStruct_0229a8cc *r1, char *r2, int r3)
{
    unsigned int val;
    int ret;
    char *p1, *p2;

    val = r1->unk_04.bits.low10;
    ret = func_ov094_0229a4c0((int) r0);
    p1 = r0 + 4 + (ret << 7);
    p2 = p1 + 0x40;

    MI_CpuCopy8(r2, p1, 0x40);
    MI_CpuCopy8(r2 + 0x400, p2, 0x40);

    func_020b9a18(r0 + 0x98c + ret * 0x38, p1, p2, 8, val, val + 1, val + 0x20, val + 0x21);

    r1->unk_04.raw = (r1->unk_04.raw & 0xffff0fff) | ((r3 & 0xF) << 12);
}
