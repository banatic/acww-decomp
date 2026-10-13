/* func_ov094_0229b088 @ 0x0229b088, 0x4c bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern void func_02064328(char *dst, const char *src);
extern void func_02064af4(char *dst, const char *src, unsigned int size);
extern unsigned int func_0206fe28(unsigned int i);
extern unsigned char data_ov094_0229c0d4[];

void *func_ov094_0229b088(char *self, int param)
{
    char buf[0x2c];
    char *p;
    int bank;

    bank = param >> 4;
    if (bank != ((unsigned char *) self)[0x804]) {
        ((unsigned char *) self)[0x804] = (unsigned char) bank;
        func_02064328(buf, (const char *) data_ov094_0229c0d4);
        func_02064af4(buf, self + 4, 0x800);
    }

    p = self + 4;
    p += func_0206fe28(param & 0xf) << 5;

    return p;
}
