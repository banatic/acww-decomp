/* func_0209cc10 @ 0x0209cc10, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02037bc4(int);
extern int func_02037bec(int);

int func_0209cc10(int a)
{
    int result = func_02037bec(func_02037bc4(a) | 0x100);
    if (result == 0x36) {
        result = a;
    }
    return result;
}
