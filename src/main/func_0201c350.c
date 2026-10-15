/* func_0201c350 @ 0x0201c350, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201c390(int a, int b);

int func_0201c350(int a, int b, int c)
{
    int result = 0;
    if (b != 0) {
        int val;
        val = func_0201c390(a, b);
        if (val < 0) {
            val = -val;
        }
        if (val < c) {
            result = 1;
        }
    }
    return result;
}
