/* func_ov004_02211b54 @ 0x02211b54, 0x26 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_022118bc(int a, int b);

void func_ov004_02211b54(int a, int b)
{
    switch (b) {
        case 0:
        case 1:
            func_ov004_022118bc(a, 1);
            break;
        case 8:
            func_ov004_022118bc(a, 0);
            break;
    }
}
