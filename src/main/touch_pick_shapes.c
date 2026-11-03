/* touch_pick_shapes: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b75b4 @ 0x020b75b4, 0x2 bytes, Thumb
 * func_020b75b0 @ 0x020b75b0, 0x2 bytes, Thumb
 * func_020b758c @ 0x020b758c, 0x24 bytes, Thumb
 * func_020b755c @ 0x020b755c, 0x2e bytes, Thumb
 * func_020b7524 @ 0x020b7524, 0x36 bytes, Thumb
 * func_020b74f0 @ 0x020b74f0, 0x34 bytes, Thumb
 * func_020b74ec @ 0x020b74ec, 0x4 bytes, Thumb
 */

struct UnkStruct_020b758c {
    int unk_00;
    int unk_04;
    int unk_08;
};

extern unsigned char func_020b8538(unsigned char);
extern int func_020b7338(int a, unsigned char b);
extern unsigned char data_021f6c38;
extern unsigned char data_021f6c34;

void func_020b75b4(void) {}

void func_020b75b0(void) {}

int func_020b758c(struct UnkStruct_020b758c *src, struct UnkStruct_020b758c *dst)
{
    if (dst != 0) {
        dst->unk_00 = src->unk_00;
        dst->unk_04 = src->unk_04;
        dst->unk_08 = src->unk_08;
    }
    return (src->unk_00 != 0xffed4000);
}

unsigned char func_020b755c(void *r0, unsigned int *r1, unsigned int *r2, unsigned char *r3)
{
    unsigned char b;

    if (r1 != 0) {
        r1[0] = *(unsigned int *) ((char *) r0 + 0xc);
        r1[1] = *(unsigned int *) ((char *) r0 + 0x10);
        r1[2] = *(unsigned int *) ((char *) r0 + 0x14);
    }
    if (r2 != 0) {
        *r2 = *(unsigned char *) ((char *) r0 + 0x18);
    }
    if (r3 != 0) {
        *r3 = *(unsigned char *) ((char *) r0 + 0x19);
    }
    b = *(unsigned char *) ((char *) r0 + 0x18);
    return func_020b8538(b);
}

int func_020b7524(int a, int *p1, unsigned char *p2)
{
    unsigned char byte_tmp;
    int word_tmp;
    int arr_tmp[3];

    if (p1 == 0) {
        p1 = &word_tmp;
    }
    if (p2 == 0) {
        p2 = &byte_tmp;
    }
    if ((int) func_020b755c((void *) a, (unsigned int *) arr_tmp, (unsigned int *) p1, p2)) {
        return func_020b7338(*p1, *p2);
    }
    return 0;
}

int func_020b74f0(int a, int b, int c)
{
    int flag;
    if (data_021f6c38 != 0 && data_021f6c34 != 0) {
        flag = 1;
    } else {
        flag = 0;
    }
    if (flag != 0) {
        return func_020b7524(a, (int *) b, (unsigned char *) c);
    }
    return 0;
}

int func_020b74ec(void)
{
    return 0;
}
