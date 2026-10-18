/* __sinit_ov034_02260020 @ 0x02260020, 0x6c bytes, Thumb, module ov034
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b6468(void *out, unsigned char b, int *data, int v, short s1, unsigned char c1, unsigned char c2, short s2,
                          unsigned char c3);
extern void __register_global_object(void *a, void *b, void *node);

extern unsigned char data_ov004_02256914[];
extern unsigned char data_ov034_022600ec[];
extern unsigned char data_ov034_0226012c[];
extern void func_020b649c(void *object);
extern unsigned char data_ov034_02260120[];

#pragma define_section INIT ".init" RX
#pragma section INIT begin

void __sinit_ov034_02260020(void)
{
    *((unsigned char *) data_ov034_022600ec + 0x1) = *(unsigned char *) data_ov004_02256914;
    {
        int d[3];
        d[0] = 0x19000;
        d[1] = 0x200;
        d[2] = 0x1a000;
        func_020b6468(data_ov034_0226012c, 0x1, d, 0x23800000, (short) 0xc000, 0x2, 0x2, (short) 0xc000, 0x3);
        __register_global_object(data_ov034_0226012c, (void *) func_020b649c, data_ov034_02260120);
    }
}

#pragma section INIT end
