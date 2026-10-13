/* func_ov003_0220c0f0 @ 0x0220c0f0, 0x22 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_0220c064(int a, int b);

void func_ov003_0220c0f0(int a, int b)
{
    switch (b) {
        case 0:
            func_ov003_0220c064(a, 1);
            break;
        case 8:
            func_ov003_0220c064(a, 0);
            break;
        default:
            break;
    }
}
