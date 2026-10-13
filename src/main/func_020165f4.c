/* func_020165f4 @ 0x020165f4, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02082fec(int a, int b);
extern void func_0205cc1c(int a, int b, int c, int d);

void func_020165f4(int a)
{
    int result = func_02082fec(a, 2);
    if (result) {
        func_0205cc1c(result, 0x143, 0, 0);
    }
}
