/* func_ov003_0221e6f0 @ 0x0221e6f0, 0x26 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_0221e580(int, int);

int func_ov003_0221e6f0(int a, int b)
{
    switch (b) {
        case 0:
        case 1:
            return func_ov003_0221e580(a, 1);
        case 8:
            return func_ov003_0221e580(a, 0);
        default:
            return a;
    }
}
