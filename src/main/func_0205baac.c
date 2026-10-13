/* func_0205baac @ 0x0205baac, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0207cec0(void *ptr, int b);
extern unsigned int func_0207f300(unsigned int x);

extern unsigned char data_021e5a2c[];

void func_0205baac(unsigned short *out, int a, int b)
{
    unsigned int r;

    r = func_0207cec0((void *) data_021e5a2c, b);
    if (r != 0) {
        r = func_0207f300(r);
        if (r < 0x44) {
            r = (unsigned short) (r + 0x1144);
        } else {
            r = 0x1144;
        }
        *out = r;
    } else {
        *out = 0x1144;
    }
}
