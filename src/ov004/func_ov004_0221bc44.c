/* func_ov004_0221bc44 @ 0x0221bc44, 0x54 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0221b98c(void *self);
extern unsigned char data_ov004_02257904;
extern unsigned char data_ov004_02257908;
extern void *data_ov004_0225797c[];

int func_ov004_0221bc44(void *self)
{
    unsigned char *p;

    if (func_ov004_0221b98c(self) != 0) {
        *((unsigned char *) self + 0x154) = 0xff;
        data_ov004_02257904 = 1;
        return 1;
    }
    p = (unsigned char *) ((char *) self + 0x154);
    *p = data_ov004_02257908;
    if (*p < 0x20) {
        data_ov004_0225797c[*p] = self;
        data_ov004_02257908 = (unsigned char) (data_ov004_02257908 + 1);
        return 1;
    }
    return 0;
}
