/* func_ov077_02278f84 @ 0x02278f84, 0x48 bytes, Thumb, module ov077
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_020c80f8;
extern void func_02019c20(void *p, int a, int b, int c);
extern void func_0200442c(void *p, int a, int b, int c);

int func_ov077_02278f84(void *p)
{
    volatile unsigned int a;
    volatile unsigned int b;
    a = data_020c80f8;
    b = 0;
    func_02019c20((char *) p + 0x564, 1, 0xfe, 1);
    func_0200442c((char *) p + 0x514, 0x7e7, 0x7f, 0);
    return 1;
}
