/* func_ov096_0229c310 @ 0x0229c310, 0x38 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

int func_ov096_0229c310(char *self)
{
    volatile long long unused;
    (void) &unused;
    if (*(unsigned char *) (self + 0xb1) == 2 && *(unsigned char *) (self + 0xb0) == 0 &&
        *(unsigned short *) (self + 0xac) >= 0x11a8 && *(unsigned short *) (self + 0xac) <= 0x12a7) {
        return 1;
    }
    return 0;
}
