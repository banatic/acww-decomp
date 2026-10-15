/* func_020980c4 @ 0x020980c4, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02066688(void *);
extern void func_02066694(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));

int func_020980c4(int param)
{
    __cxa_vec_ctor((void *) (param), 10, 256, (void (*)(void *)) func_02066694, (void (*)(void *)) func_02066688);
    return param;
}
