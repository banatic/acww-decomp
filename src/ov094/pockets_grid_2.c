/* pockets_grid_2: 4 functions, module ov094
 * mwccarm 1.2/base -O4,s
 * func_ov094_0229a958 @ 0x0229a958, 0x44 bytes, Thumb
 * func_ov094_0229a8cc @ 0x0229a8cc, 0x8c bytes, Thumb
 * func_ov094_0229a8bc @ 0x0229a8bc, 0x10 bytes, Thumb
 * func_ov094_0229a898 @ 0x0229a898, 0x22 bytes, Thumb
 */

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

extern int func_ov094_0229acb0(void *p, unsigned short *s, int t);
extern int func_ov094_0229b088(void *p, int x);
extern int func_ov094_0229b03c(void *p, int x);
extern int func_ov094_0229a4c0(int);
extern void MI_CpuCopy8(void *dst, const void *src, unsigned int size);
extern int func_020b9a18(char *a, char *b, char *c, int d, int e, int f, int g, int h);
extern int func_ov094_0229a328(int, int);
extern void func_ov094_0229a888(unsigned char, unsigned char);

void func_ov094_0229a8cc(char *r0, UnkStruct_0229a8cc *r1, char *r2, int r3);

void func_ov094_0229a958(void *p, int a, unsigned short b, int c)
{
    unsigned short local;
    int r4;
    int r7;
    int r3;

    local = b;
    r4 = func_ov094_0229acb0(p, &local, c);
    r7 = func_ov094_0229b088((char *) p + 0x184, r4);
    r3 = func_ov094_0229b03c((char *) p + 0x184, r4);
    func_ov094_0229a8cc((char *) p, (UnkStruct_0229a8cc *) a, (char *) r7, r3);
}

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

int func_ov094_0229a8bc(int p0, int p1)
{
    return func_ov094_0229a328((p0 + 2632), p1);
}

void func_ov094_0229a898(unsigned char r0, unsigned char r1, unsigned char r2)
{
    unsigned char r5 = r1;
    unsigned char r6 = r0;
    unsigned char r4 = r2;
    while (r5 <= r4) {
        func_ov094_0229a888(r6, r5);
        r5 = (unsigned char) (r5 + 1);
    }
}
