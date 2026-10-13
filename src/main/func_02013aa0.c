/* func_02013aa0 @ 0x02013aa0, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02013aa0(void *base, unsigned short value)
{
    *(unsigned short *) ((char *) base + 0x63e) = value;
}
