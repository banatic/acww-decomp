/* func_020c3b00 @ 0x020c3b00, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201c350(int a, int b, int c);

int func_020c3b00(int a, int b)
{
    int result = 0;
    if (func_0201c350(a, b, 0x2000) == 1) {
        result = 1;
    }
    return result;
}
