/* func_020ae410 @ 0x020ae410, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020051b0(void);
extern void func_02034ce0(void);
extern void __cxa_vec_ctor(void *arg, int a, int b, void (*cb1)(void), void (*cb2)(void));
extern void func_020ae724(void *ptr);

void *func_020ae410(void *arg)
{
    __cxa_vec_ctor(arg, 3, 2, func_02034ce0, func_020051b0);
    func_020ae724((char *) arg + 8);
    return arg;
}
