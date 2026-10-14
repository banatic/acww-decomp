/* func_0203652c @ 0x0203652c, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02036570(void);
extern void func_02036574(void);
extern void __cxa_vec_ctor(void *addr, int a, int b, void (*cb1)(void), void (*cb2)(void));

int *func_0203652c(int *s, int value)
{
    s[0] = value;
    __cxa_vec_ctor(s + 1, 8, 16, func_02036574, func_02036570);
    return s;
}
