/* __sinit_ov026_02260020 @ 0x02260020, 0xe8 bytes, Thumb, module ov026
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b6468(void *out, unsigned char b, int *data, int v, short s1, unsigned char c1, unsigned char c2, short s2,
                          unsigned char c3);
extern void __register_global_object(void *a, void *b, void *node);

extern unsigned char data_ov004_02256914[];
extern unsigned char data_ov026_02260174[];
extern unsigned char data_ov026_022601c4[];
extern void func_020b649c(void *object);
extern unsigned char data_ov026_022601a0[];
extern unsigned char data_ov026_022601e0[];
extern unsigned char data_ov026_022601b8[];
extern unsigned char data_ov026_022601fc[];
extern unsigned char data_ov026_022601ac[];

#pragma define_section INIT ".init" RX
#pragma section INIT begin

void __sinit_ov026_02260020(void)
{
    *((unsigned char *) data_ov026_02260174 + 0x1) = *(unsigned char *) data_ov004_02256914;
    {
        int d[3];
        d[0] = 0x16000;
        d[1] = 0x0;
        d[2] = 0x11000;
        func_020b6468(data_ov026_022601c4, 0x20, d, 0x23800000, (short) 0x0, 0x2, 0x2, (short) 0x0, 0x3);
        __register_global_object(data_ov026_022601c4, (void *) func_020b649c, data_ov026_022601a0);
    }
    {
        int d[3];
        d[0] = 0x1b000;
        d[1] = 0x0;
        d[2] = 0x1a000;
        func_020b6468(data_ov026_022601e0, 0x28, d, 0x23800000, (short) 0xc000, 0x2, 0x2, (short) 0xc000, 0x3);
        __register_global_object(data_ov026_022601e0, (void *) func_020b649c, data_ov026_022601b8);
    }
    {
        int d[3];
        d[0] = 0x1b000;
        d[1] = 0x0;
        d[2] = 0x8000;
        func_020b6468(data_ov026_022601fc, 0x28, d, 0x23800000, (short) 0xc000, 0x2, 0x2, (short) 0xc000, 0x3);
        __register_global_object(data_ov026_022601fc, (void *) func_020b649c, data_ov026_022601ac);
    }
}

#pragma section INIT end
