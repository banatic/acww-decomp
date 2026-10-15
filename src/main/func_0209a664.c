/* func_0209a664 @ 0x0209a664, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209a6ec(int);
extern void func_0209525c(int, int);

void func_0209a664(int a, int b)
{
    int ret;
    ret = func_0209a6ec(a);
    if (ret) {
        func_0209525c(ret, b);
    }
}
