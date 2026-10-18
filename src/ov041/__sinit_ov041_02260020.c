/* __sinit_ov041_02260020 @ 0x02260020, 0xe4 bytes, Thumb, module ov041
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b6468(void *out, unsigned char b, int *data, int v, short s1, unsigned char c1, unsigned char c2, short s2,
                          unsigned char c3);
extern void __register_global_object(void *a, void *b, void *node);

extern unsigned char data_ov004_02256914[];
extern unsigned char data_ov041_02260168[];
extern unsigned char data_ov041_022601e4[];
extern void func_020b649c(void *object);
extern unsigned char data_ov041_022601c0[];
extern unsigned char data_ov041_02260200[];
extern unsigned char data_ov041_022601cc[];
extern unsigned char data_ov041_0226021c[];
extern unsigned char data_ov041_022601d8[];

#pragma define_section INIT ".init" RX
#pragma section INIT begin

void __sinit_ov041_02260020(void)
{
    *((unsigned char *) data_ov041_02260168 + 0x1) = *(unsigned char *) data_ov004_02256914;
    {
        int d[3];
        d[0] = 0x0;
        d[1] = 0x0;
        d[2] = 0x0;
        func_020b6468(data_ov041_022601e4, 0x3c, d, 0x0, (short) 0x0, 0x2, 0x2, (short) 0x0, 0x4);
        __register_global_object(data_ov041_022601e4, (void *) func_020b649c, data_ov041_022601c0);
    }
    {
        int d[3];
        d[0] = 0x10000;
        d[1] = 0x200;
        d[2] = 0x9000;
        func_020b6468(data_ov041_02260200, 0x1e, d, 0x10c00000, (short) 0x0, 0x2, 0x2, (short) 0x8000, 0x1);
        __register_global_object(data_ov041_02260200, (void *) func_020b649c, data_ov041_022601cc);
    }
    {
        int d[3];
        d[0] = 0x10000;
        d[1] = 0x200;
        d[2] = 0x1d000;
        func_020b6468(data_ov041_0226021c, 0x1f, d, 0x23800000, (short) 0x8000, 0x2, 0x2, (short) 0x8000, 0x3);
        __register_global_object(data_ov041_0226021c, (void *) func_020b649c, data_ov041_022601d8);
    }
}

#pragma section INIT end
