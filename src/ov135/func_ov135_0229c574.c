/* func_ov135_0229c574 @ 0x0229c574, 0x12 bytes, Thumb, module ov135
 * mwccarm 1.2/base -O4,s
 */

int func_ov135_0229c574(char *p, unsigned int mask)
{
    unsigned int tmp;
    tmp = *(unsigned short *) (p + 0x92) & mask;
    if (tmp == 0) {
        return 0;
    } else {
        return 1;
    }
}
