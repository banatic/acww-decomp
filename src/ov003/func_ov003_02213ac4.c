/* func_ov003_02213ac4 @ 0x02213ac4, 0x20 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02213ab4(unsigned char *p, short e);

void func_ov003_02213ac4(unsigned char *p, unsigned char a, unsigned char b, unsigned char c, unsigned char d, short e)
{
    p[0] = a;
    p[1] = b;
    p[2] = c;
    p[3] = d;
    func_ov003_02213ab4(p, e);
}
