/* func_0203652c @ 0x0203652c, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02036570(void *);
extern int func_02036574(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));

int *func_0203652c(int *s, int value)
{
    s[0] = value;
    __cxa_vec_ctor((void *) (s + 1), 8, 16, (((void (*)(void *)) func_02036574)), (void (*)(void *)) func_02036570);
    return s;
}
