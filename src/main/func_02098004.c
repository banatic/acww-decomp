/* func_02098004 @ 0x02098004, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02066688(void);
extern void __cxa_vec_cleanup(int arg, int a, int b, void (*cb)(void));

int func_02098004(int arg)
{
    __cxa_vec_cleanup(arg, 0xa, 0x100, func_02066688);
    return arg;
}
