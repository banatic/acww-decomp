/* func_020985a0 @ 0x020985a0, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void *func_02099ad0(void *);
extern void *func_02099bc8(void *);

void *func_020985a0(void *arg)
{
    __cxa_vec_ctor((void *) (arg), 3, 0x249c, (((void (*)(void *)) func_02099bc8)), (((void (*)(void *)) func_02099ad0)));
    return arg;
}
