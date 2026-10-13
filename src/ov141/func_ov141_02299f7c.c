/* func_ov141_02299f7c @ 0x02299f7c, 0x18 bytes, Thumb, module ov141
 * mwccarm 1.2/base -O4,s
 */

int func_ov141_02299f7c(unsigned short *base, unsigned int mask)
{
    if ((*(unsigned short *) ((char *) base + 0x1a7c) & mask) != 0) {
        return 1;
    }
    return 0;
}
