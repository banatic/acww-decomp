/* town_villager_3: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02080ce4 @ 0x02080ce4, 0xc bytes, Thumb
 * func_02080cd8 @ 0x02080cd8, 0xc bytes, Thumb
 */

int func_02080ce4(int r0)
{
    return r0 + 0x7d2;
}

void func_02080cd8(unsigned char *dest, unsigned short *src)
{
    *(unsigned short *) (dest + 0x7d2) = *src;
}
