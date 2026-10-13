/* func_ov003_0222c704 @ 0x0222c704, 0x16 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

int func_ov003_0222c704(unsigned short *p)
{
    if (*p == 0x5b || (*p >= 0x66 && *p <= 0x6d)) {
        return 1;
    }
    return 0;
}
