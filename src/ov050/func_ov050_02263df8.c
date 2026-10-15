/* func_ov050_02263df8 @ 0x02263df8, 0x24 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019c6c(int a, int b, int c);

int func_ov050_02263df8(int a)
{
    func_02019c6c(a + 0x564, 1, *(unsigned short *) ((char *) a + 0x730));
    return 1;
}
