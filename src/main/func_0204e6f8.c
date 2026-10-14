/* func_0204e6f8 @ 0x0204e6f8, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_ctor(int, int, int, void (*)(void), void (*)(void));
extern void func_020051b0(void);
extern void func_02034ce0(void);

int func_0204e6f8(int param)
{
    __cxa_vec_ctor(param, 0x100, 2, func_02034ce0, func_020051b0);
    return param;
}
