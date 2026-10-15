/* func_ov068_02274790 @ 0x02274790, 0x80 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019c20(void *, int, int, int, unsigned short, int);
extern int func_ov004_02246eb8(void);
extern void func_0201acbc(void *, int, int, int, short, short);
extern int func_020147e0(void *, int, int);
extern void func_02035684(int, int, int);
extern void func_020355b8(void);

extern short data_020c80ec;
extern short data_020c80f4;
extern unsigned short data_020c80f8;

int func_ov068_02274790(void *p)
{

    (void) ((void *) func_02019c20((char *) p + 0x564, 1, 0x102, 0, data_020c80f8, 0));
    func_ov004_02246eb8();
    func_0201acbc((char *) p + 0x3b0, 0, 0, 0x1000, data_020c80f4, data_020c80ec);
    func_020147e0((char *) p + 0x618, 0, 1);
    func_02035684(0x10, 0xf, 0);
    func_020355b8();
    return 1;
}
