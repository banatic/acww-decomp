/* func_02082438 @ 0x02082438, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207cec0(void *p);
extern void *func_0208150c(void);
extern int func_02003618(void *ptr, void *a);
extern void func_020b4a20(void *a, unsigned char *c, void *d);

extern int data_021e5a2c;
extern int data_020e19b8;

int func_02082438(void *a, unsigned short *b)
{
    unsigned short v = *b;
    int low = v & 0xfff;
    int result = 0;
    int high = (v & 0xf000) >> 12;

    if (high != 13) {
        if (high == 14) {
            if (func_0207cec0(&data_021e5a2c)) {
                result = func_02003618(func_0208150c(), a);
            }
        }
    } else {
        if (low < 0x26) {
            unsigned char c = (unsigned char) low;
            func_020b4a20(a, &c, &data_020e19b8);
            result = 1;
        }
    }
    return result;
}
