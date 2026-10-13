/* func_020aec90 @ 0x020aec90, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020aef8c(int a, int b);
extern int func_020b0164(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7);

int func_020aec90(int a, int b)
{
    return func_020b0164(a + 4, b, 4, 0, func_020aef8c(a, b), 37, 0);
}
