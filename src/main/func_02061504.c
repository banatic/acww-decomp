/* func_02061504 @ 0x02061504, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020051b0(void *);
extern void func_02034ce0(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));

int func_02061504(int arg)
{
    __cxa_vec_ctor((void *) (arg), 0x100, 2, (void (*)(void *)) func_02034ce0, (void (*)(void *)) func_020051b0);
    return arg;
}
