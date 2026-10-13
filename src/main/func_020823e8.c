/* func_020823e8 @ 0x020823e8, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

/* FAKEMATCH: the repeated type test keeps the case-14 code before the case-13 code; a switch or a single test reorders the blocks */

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
    if (type != 13) {
        if (((v & 0xf000) >> 12) == 14) {
            void *r = func_0207cec0((void *) data_021e5a2c, low12);
            if (r) {
                void *r2 = func_0208150c(r);
                result = func_0200364c(r2);
            }
        }
    } else {
        void *r = func_020824d0(p);
        if (r) {
            result = *(((unsigned char *) r) + 1);
        }
    }
    return result;
}
