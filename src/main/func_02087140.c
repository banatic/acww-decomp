/* func_02087140 @ 0x02087140, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02087140(volatile unsigned char *p)
{
    *p &= ~0x01;
    *p &= ~0x0e;
    *p &= ~0x70;
    *p &= ~0x80;
}
