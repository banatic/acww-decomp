/* func_020786f8 @ 0x020786f8, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020786f8(char *p, char a, char b, char c)
{
    p[0] = ((a << 4) & 0xf0) | (b & 0xf);
    p[1] = c;
}
