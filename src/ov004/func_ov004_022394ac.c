/* func_ov004_022394ac @ 0x022394ac, 0x16 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_02239460(char *a, char *b);
int func_ov004_022394ac(char *a, char *b)
{
    int n = func_ov004_02239460(a, b);
    if (n == 0) {
        n = 1;
    }
    return n << 12;
}
