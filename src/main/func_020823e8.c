/* func_020823e8 @ 0x020823e8, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0207cec0(void *base, int val);
extern void *func_0208150c(void *ptr);
extern int func_0200364c(void *ptr);
extern void *func_020824d0(unsigned short *p);
extern unsigned char data_021e5a2c[];

int func_020823e8(unsigned short *p)
{
    unsigned short v = *p;
    int low12 = v & 0xfff;
    int type = (v & 0xf000) >> 12;
    int result = 5;
    switch (type) {
        case 14: {
            void *r = func_0207cec0((void *) data_021e5a2c, low12);
            if (r) {
                result = func_0200364c(func_0208150c(r));
            }
            break;
        }
        case 13: {
            void *r = func_020824d0(p);
            if (r) {
                result = *(((unsigned char *) r) + 1);
            }
            break;
        }
    }
    return result;
}
