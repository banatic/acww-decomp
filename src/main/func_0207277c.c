/* func_0207277c @ 0x0207277c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern volatile unsigned char data_021d0468;
int func_0207277c(int a, int bit)
{
    int r;
    if (((data_021d0468 >> bit) & 1) != 0) {
        r = 1;
    } else {
        r = 0;
    }
    data_021d0468 = (unsigned char) (data_021d0468 & ~(1 << bit));
    return r;
}
