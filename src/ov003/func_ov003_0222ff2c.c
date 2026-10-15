/* func_ov003_0222ff2c @ 0x0222ff2c, 0x48 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0209d238(char *a, unsigned char *b);
extern void func_0209d0a4(unsigned char *p);

int func_ov003_0222ff2c(char *a, unsigned char *o)
{
    if (o[0x250] == 0) {
        o[0x250] = 2;
        func_0209d238(a + 0x50, o + 0x230);
        func_0209d0a4(o + 0x130);
        o[0x249] = 0;
        return 1;
    }
    return 0;
}
