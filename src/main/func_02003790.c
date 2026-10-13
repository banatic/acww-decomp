/* func_02003790 @ 0x02003790, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020642a8(void *src, void *dst);

void func_02003790(void *src, void *dst)
{
    unsigned char *s = (unsigned char *) src;
    unsigned char *d = (unsigned char *) dst;

    func_020642a8(src, dst);
    d[0xf] = s[0xf];
    d[0xe] = s[0xe];
}
