/* func_02087b30 @ 0x02087b30, 0x46 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int);

void func_02087b30(unsigned char *p)
{
    *p = (*p & ~0x0C) | (((unsigned char) func_020644cc(3) & 3) << 2);
    *p = (*p & ~0x30) | (((unsigned char) func_020644cc(4) & 3) << 4);
    *p |= 2;
}
