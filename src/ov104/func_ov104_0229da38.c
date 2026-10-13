/* func_ov104_0229da38 @ 0x0229da38, 0x24 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

// not used, but we must declare any referenced externs if needed; here none

unsigned char func_ov104_0229da38(int a, unsigned int b)
{
    if (b >= 11 && b <= 20) {
        return (unsigned char) (b - 11);
    }
    if (b >= 21 && b <= 30) {
        return (unsigned char) (b + 24);
    }
    return 0;
}
