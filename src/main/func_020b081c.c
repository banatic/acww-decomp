/* func_020b081c @ 0x020b081c, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b0a80(void);
extern void __cxa_vec_cleanup(int, int, int, int);

int func_020b081c(int a)
{
    __cxa_vec_cleanup(a, 3, 6, (int) func_020b0a80);
    return a;
}
