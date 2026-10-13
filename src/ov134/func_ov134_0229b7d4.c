/* func_ov134_0229b7d4 @ 0x0229b7d4, 0x34 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov134_0229b5ac(void *p, int b, int c, int d, int e, int f, int g);

void func_ov134_0229b7d4(void *p)
{
    int tmp = *(unsigned char *) ((char *) p + 0xbd) + 0x7d0;
    func_ov134_0229b5ac(p, *(unsigned char *) ((char *) p + 0xa3), 0x180, 5, tmp, 0xf, 0);
}
