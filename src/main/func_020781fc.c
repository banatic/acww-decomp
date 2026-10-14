/* func_020781fc @ 0x020781fc, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_ctor(int, int, int, void (*)(void), void (*)(void));
extern void func_020782d0(void);
extern void func_020782d4(void);

int func_020781fc(int arg0)
{
    __cxa_vec_ctor(arg0, 15, 196, func_020782d4, func_020782d0);
    return arg0;
}
