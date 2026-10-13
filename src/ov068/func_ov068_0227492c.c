/* func_ov068_0227492c @ 0x0227492c, 0xb0 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201ad18(void *, int, int, int, int, int, int, int);
extern void func_02019c20(void *, int, int, int, int, int);
extern void func_0201acbc(void *, int, int, int, int, int);
extern int data_020c814c;
extern unsigned short data_020c80f8;
extern short data_020c80f4;
extern short data_020c80ec;

extern unsigned char data_021fbee8[];

int func_ov068_0227492c(void *self)
{
    if (*(int *) ((char *) self + 0x730) == 7) {
        func_0201ad18((char *) self + 0x3b0, 0, 0, 0, (unsigned int) data_021fbee8, 4, data_020c814c, 1);
        func_02019c20((char *) self + 0x564, 1, 0x105, 0, data_020c80f8, 0);
        func_0201acbc((char *) self + 0x3b0, 0, -3096, 0, data_020c80f4, data_020c80ec);
    } else {
        func_0201ad18((char *) self + 0x3b0, 1, 0, 0, (unsigned int) data_021fbee8, 4, data_020c814c, 1);
    }
    return 1;
}
