/* func_ov068_0227570c @ 0x0227570c, 0x60 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_020c80f8;
extern void *data_020c814c;

extern int func_02019c6c(void *self, int a, int b);
extern void func_0201ad18(void *self, int a, int b, int c, int d, int e, void *f, int g);
extern void func_02030864(int a);

extern unsigned char data_021fbee8[];

int func_ov068_0227570c(void *param)
{
    if (func_02019c6c((char *) param + 0x564, 1, data_020c80f8) != 0) {
        func_0201ad18((char *) param + 0x3b0, 1, 0, 0, (unsigned int) data_021fbee8, 4, data_020c814c, 1);
        func_02030864(0);
        return 1;
    }
    return 0;
}
