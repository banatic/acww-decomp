/* func_0200149c @ 0x0200149c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_0200149c(void)
{
    while ((int) *(volatile unsigned short *) 0x04000006 >= 0xC0)
        ;
    while ((int) *(volatile unsigned short *) 0x04000006 < 0xC0)
        ;
}
