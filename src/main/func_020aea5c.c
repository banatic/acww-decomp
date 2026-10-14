/* func_020aea5c @ 0x020aea5c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020051b0(void);
extern void func_02034ce0(void);
extern void __cxa_vec_ctor(int, int, int, void (*)(void), void (*)(void));

int func_020aea5c(int param)
{
    __cxa_vec_ctor(param, 6, 2, func_02034ce0, func_020051b0);
    return param;
}
