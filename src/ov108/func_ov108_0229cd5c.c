/* func_ov108_0229cd5c @ 0x0229cd5c, 0x14 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

int func_ov108_0229cd5c(int a, unsigned int b)
{
    if (b < 0xb) {
        goto zero;
    }
    if (b > 0x14) {
        goto zero;
    }
    return (unsigned char) (b - 0xb);
zero:
    return 0;
}
