/* func_ov004_022315ec @ 0x022315ec, 0x26 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0223121c(int a, int b);

void func_ov004_022315ec(int a, int b)
{
    switch (b) {
        case 0:
        case 1:
            func_ov004_0223121c(a, 1);
            break;
        case 8:
            func_ov004_0223121c(a, 0);
            break;
    }
}
