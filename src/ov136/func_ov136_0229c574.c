/* func_ov136_0229c574 @ 0x0229c574, 0x18 bytes, Thumb, module ov136
 * mwccarm 1.2/base -O4,s
 */

int func_ov136_0229c574(void *p, int mask)
{
    if (((*(unsigned short *) ((char *) p + 0x2b74)) & mask) != 0) {
        return 1;
    }
    return 0;
}
