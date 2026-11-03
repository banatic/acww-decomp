/* item_1568_count: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020871c8 @ 0x020871c8, 0x2 bytes, Thumb
 * func_020871c4 @ 0x020871c4, 0x2 bytes, Thumb
 * func_020871b8 @ 0x020871b8, 0xc bytes, Thumb
 * func_020871b0 @ 0x020871b0, 0x8 bytes, Thumb
 * func_020871a8 @ 0x020871a8, 0x8 bytes, Thumb
 * func_0208718c @ 0x0208718c, 0x1a bytes, Thumb
 * func_02087178 @ 0x02087178, 0x12 bytes, Thumb
 * func_0208716c @ 0x0208716c, 0xa bytes, Thumb
 */

struct BitFields {
    unsigned char value : 3;
    unsigned char rest : 5;
};

extern void MI_CpuFill8(int a, int b, int c);

void func_020871c8(void *self) {}

void func_020871c4(void *self) {}

void func_020871b8(int a)
{
    MI_CpuFill8(a, 0, 1);
}

void func_020871b0(int argument0)
{
    func_020871b8((int) argument0);
}

int func_020871a8(unsigned char *p0)
{
    return (int) ((unsigned int) ((p0[0] << 29)) >> 29);
}

void func_0208718c(struct BitFields *p)
{
    p->value = p->value + 1;
}

int func_02087178(const unsigned char *p)
{
    if ((((unsigned) *p << 28) >> 31) == 1) {
        return 1;
    } else {
        return 0;
    }
}

void func_0208716c(unsigned char *p)
{
    p[0] = (unsigned char) (p[0] | 8);
}
