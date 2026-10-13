/* func_ov003_0221b944 @ 0x0221b944, 0x26 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_0221b8b8(int a, int b);

void func_ov003_0221b944(int a, int b)
{
    switch (b) {
        case 0:
        case 1:
            func_ov003_0221b8b8(a, 1);
            break;
        case 8:
            func_ov003_0221b8b8(a, 0);
            break;
    }
}
