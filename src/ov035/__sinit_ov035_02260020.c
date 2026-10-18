/* __sinit_ov035_02260020 @ 0x02260020, 0xb4 bytes, Thumb, module ov035
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b6468(void *out, unsigned char b, int *data, int v, short s1, unsigned char c1, unsigned char c2, short s2,
                          unsigned char c3);
extern void __register_global_object(void *a, void *b, void *node);

extern unsigned char data_ov004_02256914[];
extern unsigned char data_ov035_0226012c[];
extern unsigned char data_ov035_02260178[];
extern void func_020b649c(void *object);
extern unsigned char data_ov035_02260160[];
extern unsigned char data_ov035_02260194[];
extern unsigned char data_ov035_0226016c[];

#pragma define_section INIT ".init" RX
#pragma section INIT begin

void __sinit_ov035_02260020(void)
{
    *((unsigned char *) data_ov035_0226012c + 0x1) = *(unsigned char *) data_ov004_02256914;
    {
        int d[3];
        d[0] = 0x11000;
        d[1] = 0x200;
        d[2] = 0x1d000;
        func_020b6468(data_ov035_02260178, 0x7, d, 0x10c00000, (short) 0xc000, 0x2, 0x2, (short) 0x4000, 0x1);
        __register_global_object(data_ov035_02260178, (void *) func_020b649c, data_ov035_02260160);
    }
    {
        int d[3];
        d[0] = 0xf000;
        d[1] = 0x200;
        d[2] = 0x1d000;
        func_020b6468(data_ov035_02260194, 0x1, d, 0x11000000, (short) 0x4000, 0x2, 0x2, (short) 0xc000, 0x2);
        __register_global_object(data_ov035_02260194, (void *) func_020b649c, data_ov035_0226016c);
    }
}

#pragma section INIT end
