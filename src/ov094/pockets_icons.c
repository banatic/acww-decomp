/* pockets_icons: 2 functions, module ov094
 * mwccarm 1.2/base -O4,s
 * func_ov094_0229b048 @ 0x0229b048, 0x40 bytes, Thumb
 * func_ov094_0229b03c @ 0x0229b03c, 0xc bytes, Thumb
 */

extern int func_02064328(char *dst, const char *src);
extern int func_02064af4(char *dst, const char *src, unsigned int size);
extern unsigned int func_0206fe28(unsigned int i);
extern unsigned char data_ov094_0229c0c0[];
extern unsigned char data_ov094_0229bc8c[];

void *func_ov094_0229b048(char *self, unsigned int idx, unsigned int unused)
{
    char buf[0x28];
    char *p;

    func_02064328(buf, (const char *) data_ov094_0229c0c0);
    func_02064af4(buf, self + 4, 0x800);

    p = self + 4;
    p += func_0206fe28(idx) << 5;

    ((unsigned char *) self)[0x804] = 0xff;

    return p;
}

unsigned char func_ov094_0229b03c(int unused, int index)
{
    return data_ov094_0229bc8c[index];
}
