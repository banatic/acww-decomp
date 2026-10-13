/* func_ov004_0221af08 @ 0x0221af08, 0x22 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0221ae7c(int a, int b);

void func_ov004_0221af08(int a, int b)
{
    switch (b) {
        case 0:
            func_ov004_0221ae7c(a, 1);
            break;
        case 8:
            func_ov004_0221ae7c(a, 0);
            break;
        default:
            break;
    }
}
