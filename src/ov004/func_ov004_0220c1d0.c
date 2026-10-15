/* func_ov004_0220c1d0 @ 0x0220c1d0, 0x22 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0220c144(int a, int b);

void func_ov004_0220c1d0(int a, int b)
{
    switch (b) {
        case 0:
            func_ov004_0220c144(a, 1);
            break;
        case 8:
            func_ov004_0220c144(a, 0);
            break;
        default:
            break;
    }
}
