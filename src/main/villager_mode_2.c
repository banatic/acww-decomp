/* villager_mode_2: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0207dd10 @ 0x0207dd10, 0xc bytes, Thumb
 * func_0207dcf4 @ 0x0207dcf4, 0x1c bytes, Thumb
 */

unsigned char func_0207dd10(unsigned char *r0)
{
    return r0[0x7d7];
}

void func_0207dcf4(unsigned char *p)
{
    p += 0x7d7;
    *p += 1;
    if (*p >= 6) {
        *p = 0;
    }
}
