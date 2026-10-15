/* func_02008910 @ 0x02008910, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020109fc(void *obj, int a, int b, int c);

void func_02008910(void *obj, const unsigned char *src, int previous)
{
    unsigned char *p = (unsigned char *) obj + 0x7d4;
    *p = src[0xc];
    p[1] = 0;
    func_020109fc(obj, 0, 3, 3);
}
