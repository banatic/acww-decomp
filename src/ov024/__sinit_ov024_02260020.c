/* __sinit_ov024_02260020 @ 0x02260020, 0xd8 bytes, Thumb, module ov024
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b6468(void *out, unsigned char b, int *data, int v, short s1, unsigned char c1, unsigned char c2, short s2,
                          unsigned char c3);
extern void __register_global_object(void *a, void *b, void *node);
extern void func_020012dc(void);
extern void func_020b649c(void);

extern unsigned char data_ov004_02256914;
extern unsigned char data_ov024_0226014c[];
extern int data_ov024_022601a4[3];
extern unsigned char data_ov024_02260180[];
extern unsigned char data_ov024_022601b0[];
extern unsigned char data_ov024_0226018c[];
extern unsigned char data_ov024_022601cc[];
extern unsigned char data_ov024_02260198[];

void __sinit_ov024_02260020(void)
{
    *((unsigned char *) data_ov024_0226014c + 9) = data_ov004_02256914;

    data_ov024_022601a4[0] = 0x10000;
    data_ov024_022601a4[1] = 0x200;
    data_ov024_022601a4[2] = 0x1d000;
    __register_global_object(data_ov024_022601a4, (void *) func_020012dc, data_ov024_02260180);

    {
        int d[3];
        d[0] = 0x17000;
        d[1] = 0;
        d[2] = 0x14000;
        func_020b6468(data_ov024_022601b0, 0x20, d, 0x23800000, (short) 0xffffc000, 2, 2, (short) 0xffffc000, 3);
        __register_global_object(data_ov024_022601b0, (void *) func_020b649c, data_ov024_0226018c);
    }
    {
        int d[3];
        d[0] = data_ov024_022601a4[0];
        d[1] = data_ov024_022601a4[1];
        d[2] = data_ov024_022601a4[2];
        func_020b6468(data_ov024_022601cc, 0x26, d, 0x23800000, (short) 0xffff8000, 2, 2, (short) 0xffff8000, 3);
        __register_global_object(data_ov024_022601cc, (void *) func_020b649c, data_ov024_02260198);
    }
}
