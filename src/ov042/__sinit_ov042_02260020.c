/* __sinit_ov042_02260020 @ 0x02260020, 0x9c bytes, Thumb, module ov042
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b6468(void *out, unsigned char b, int *data, int v, short s1, unsigned char c1, unsigned char c2, short s2,
                          unsigned char c3);
extern void __register_global_object(void *a, void *b, void *node);

extern unsigned char data_ov004_02256914[];
extern unsigned char data_ov042_02260128[];
extern unsigned char data_ov042_02260198[];
extern void func_020b649c(void *object);
extern unsigned char data_ov042_0226018c[];
extern unsigned char data_ov042_022601b4[];
extern unsigned char data_ov042_02260180[];

#pragma define_section INIT ".init" RX
#pragma section INIT begin

void __sinit_ov042_02260020(void)
{
    *((unsigned char *) data_ov042_02260128 + 0x1) = *(unsigned char *) data_ov004_02256914;
    {
        int d[3];
        d[0] = 0x10000;
        d[1] = 0x200;
        d[2] = 0x9000;
        func_020b6468(data_ov042_02260198, 0x1d, d, 0x11000000, (short) 0x0, 0x2, 0x2, (short) 0x8000, 0x2);
        __register_global_object(data_ov042_02260198, (void *) func_020b649c, data_ov042_0226018c);
    }
    {
        int d[3];
        d[0] = 0x0;
        d[1] = 0x0;
        d[2] = 0x0;
        func_020b6468(data_ov042_022601b4, 0x3c, d, 0x0, (short) 0x0, 0x2, 0x2, (short) 0x0, 0x0);
        __register_global_object(data_ov042_022601b4, (void *) func_020b649c, data_ov042_02260180);
    }
}

#pragma section INIT end
