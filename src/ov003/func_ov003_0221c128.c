/* func_ov003_0221c128 @ 0x0221c128, 0x42 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov009_022633ac(int a, unsigned int b, int c);
extern void func_ov003_0221bfa8(int a, int flag);

void func_ov003_0221c128(int a, unsigned int b, int c)
{
    switch (b) {
        case 6:
            func_ov009_022633ac(a, b, c);
            break;
        case 0:
        case 1:
            func_ov003_0221bfa8(a, 1);
            break;
        case 8:
            func_ov003_0221bfa8(a, 0);
            break;
        default:
            break;
    }
}
