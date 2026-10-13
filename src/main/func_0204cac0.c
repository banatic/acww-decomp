/* func_0204cac0 @ 0x0204cac0, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_0204cac0(unsigned char *p, int a, int b)
{
    if (a == 4) {
        int c = *(signed char *) (p + 0x21);
        if (c < 0) {
            *(signed char *) (p + 0x21) = 1;
        } else {
            *(signed char *) (p + 0x21) = c + b;
        }
    } else {
        *(signed char *) (p + 0x21) = -1;
    }
}
