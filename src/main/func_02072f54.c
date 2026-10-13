/* func_02072f54 @ 0x02072f54, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02072f54(int a, int b)
{
    unsigned char temp = (unsigned char) (b & 0x0F);
    *((unsigned char *) (a + 0x32)) = (*((unsigned char *) (a + 0x32)) & ~0xF0) | ((temp & 0x0F) << 4);
}
