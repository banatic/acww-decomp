/* func_0203cff8 @ 0x0203cff8, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203d064(void *a, unsigned short *b, int c);
extern void *func_02072da0(void *p);
extern void *func_02072d4c(void *p);
extern void *func_02072f88(void *v);
extern void *func_0203cfe4(void *object);
extern void *func_0203cfd0(void *object);
extern void MI_CpuCopy8(void *dest, const void *src, unsigned int size);

int func_0203cff8(void *a, void *p)
{
    unsigned short val = 0x11a8;
    void *tmp;

    if (func_0203d064(a, &val, 0) == 0) {
        goto zero;
    }
    if (p == 0) {
        goto one;
    }

    tmp = func_02072da0(p);
    MI_CpuCopy8(tmp, func_0203cfe4(a), 0x200U);

    p = func_02072f88(func_02072d4c(p));
    MI_CpuCopy8(p, func_0203cfd0(a), 0x20U);

    return 1;
one:
    return 1;
zero:
    return 0;
}
