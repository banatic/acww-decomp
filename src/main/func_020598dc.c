/* func_020598dc @ 0x020598dc, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0205996c(int a, int b, int c);
extern void func_02059904(int a, int b);

int func_020598dc(int a, int b, int c)
{
    int result = 0;
    if (func_0205996c(a, c, 0) == 1) {
        func_02059904(a, b);
        result = 1;
    }
    return result;
}
