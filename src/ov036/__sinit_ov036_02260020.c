/* __sinit_ov036_02260020 @ 0x02260020, 0x58 bytes, Thumb, module ov036
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b6468(void *out, unsigned char b, int *data, int v, short s1, unsigned char c1, unsigned char c2, short s2,
                          unsigned char c3);
extern void __register_global_object(void *a, void *b, void *node);

extern unsigned char data_ov004_02256914[];
extern unsigned char data_ov036_022600d0[];
extern unsigned char data_ov036_0226012c[];
extern void func_020b649c(void *object);
extern unsigned char data_ov036_02260120[];

#pragma define_section INIT ".init" RX
#pragma section INIT begin

void __sinit_ov036_02260020(void)
{
    *((unsigned char *) data_ov036_022600d0 + 0x9) = *(unsigned char *) data_ov004_02256914;
    {
        int d[3];
        d[0] = 0x0;
        d[1] = 0x0;
        d[2] = 0x0;
        func_020b6468(data_ov036_0226012c, 0x3c, d, 0x800000, (short) 0x0, 0x2, 0x2, (short) 0x0, 0x4);
        __register_global_object(data_ov036_0226012c, (void *) func_020b649c, data_ov036_02260120);
    }
}

#pragma section INIT end
