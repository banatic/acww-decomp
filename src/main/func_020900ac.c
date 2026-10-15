/* func_020900ac @ 0x020900ac, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));

extern void *func_020901a0(void *);
extern void *func_020901d8(void *);

int func_020900ac(int arg)
{
    __cxa_vec_ctor((void *) (arg), 3, 0x950, (((void (*)(void *)) func_020901d8)), (((void (*)(void *)) func_020901a0)));
    return arg;
}
