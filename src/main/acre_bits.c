/* acre_bits: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02037d10 @ 0x02037d10, 0x2 bytes, Thumb
 * func_02037d0c @ 0x02037d0c, 0x2 bytes, Thumb
 * func_02037d00 @ 0x02037d00, 0xc bytes, Thumb
 * func_02037ce0 @ 0x02037ce0, 0x1e bytes, Thumb
 * func_02037cc0 @ 0x02037cc0, 0x1e bytes, Thumb
 * func_02037c9c @ 0x02037c9c, 0x24 bytes, Thumb
 * func_02037c78 @ 0x02037c78, 0x24 bytes, Thumb
 */

extern void MI_CpuFill8(void *dst, int c, unsigned int n);

void func_02037d10(void *object) {}

void func_02037d0c(void *object) {}

void func_02037d00(void *dst)
{
    MI_CpuFill8(dst, 0, 0x20);
}

int func_02037ce0(int unused, unsigned short *ptr, int index)
{
    int ret = 0;
    if (index >= 0 && index < 16) {
        *ptr |= (1 << index);
        ret = 1;
    }
    return ret;
}

int func_02037cc0(int unused, unsigned short *ptr, int index)
{
    int result = 0;
    if (index >= 0 && index < 16) {
        unsigned short val = *ptr;
        result = 1;
        val &= ~(1 << index);
        *ptr = val;
    }
    return result;
}

int func_02037c9c(unsigned short *base, unsigned int a, unsigned int b)
{
    int ret = 0;
    if (a < 16 && b < 16) {
        ret = func_02037ce0((int) base, base + b, a);
    }
    return ret;
}

int func_02037c78(short *p, unsigned int a, unsigned int b)
{
    int result = 0;
    if (a < 16 && b < 16) {
        result = func_02037cc0((int) p, (unsigned short *) (p + b), a);
    }
    return result;
}
