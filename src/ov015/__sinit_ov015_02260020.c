/* __sinit_ov015_02260020 @ 0x02260020, 0xbc bytes, Thumb, module ov015
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b6468(void *out, unsigned char b, int *data, int v, short s1, unsigned char c1, unsigned char c2, short s2,
                          unsigned char c3);
extern void __register_global_object(void *a, void *b, void *node);

extern unsigned char data_ov004_02256914[];
extern unsigned char data_ov015_02260150[];
extern unsigned char data_ov015_022601e4[];
extern void func_020b649c(void *object);
extern unsigned char data_ov015_022601d8[];
extern unsigned char data_ov015_02260200[];
extern unsigned char data_ov015_022601c0[];
extern unsigned char data_ov015_0226021c[];
extern unsigned char data_ov015_022601cc[];

#pragma define_section INIT ".init" RX
#pragma section INIT begin

void __sinit_ov015_02260020(void)
{
    *((unsigned char *) data_ov015_02260150 + 0x1) = *(unsigned char *) data_ov004_02256914;
    {
        int d[3];
        d[0] = 0x0;
        d[1] = 0x0;
        d[2] = 0x0;
        func_020b6468(data_ov015_022601e4, 0x3d, d, 0x800000, (short) 0x0, 0x2, 0x2, (short) 0x0, 0x4);
        __register_global_object(data_ov015_022601e4, (void *) func_020b649c, data_ov015_022601d8);
    }
    {
        int d[3];
        d[0] = 0x0;
        d[1] = 0x0;
        d[2] = 0x0;
        func_020b6468(data_ov015_02260200, 0x3f, d, 0x800000, (short) 0x0, 0x2, 0x2, (short) 0x0, 0x0);
        __register_global_object(data_ov015_02260200, (void *) func_020b649c, data_ov015_022601c0);
    }
    {
        int d[3];
        d[0] = 0x0;
        d[1] = 0x0;
        d[2] = 0x0;
        func_020b6468(data_ov015_0226021c, 0x2f, d, 0x800000, (short) 0x0, 0x2, 0x2, (short) 0x0, 0x0);
        __register_global_object(data_ov015_0226021c, (void *) func_020b649c, data_ov015_022601cc);
    }
}

#pragma section INIT end
