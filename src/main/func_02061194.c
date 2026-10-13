/* func_02061194 @ 0x02061194, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02061194(char *buf, unsigned short *src, int flag)
{
    unsigned char *p;

    *(unsigned short *) (buf + 0x44a) = *src;
    p = (unsigned char *) buf + 0x44e;
    *p = (*p & ~2) | (((unsigned char) flag & 1) << 1);
}
