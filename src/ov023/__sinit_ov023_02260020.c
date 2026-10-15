/* __sinit_ov023_02260020 @ 0x02260020, 0xa0 bytes, Thumb, module ov023
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b6468(void *out, unsigned char b, int *data, int v, short s1, unsigned char c1, unsigned char c2, short s2,
                          unsigned char c3);
extern void __register_global_object(void *a, void *b, void *node);

extern unsigned char data_ov004_02256914[];
extern unsigned char data_ov023_02260130[];
extern unsigned char data_ov023_02260178[];
extern void func_020b649c(void *object);
extern unsigned char data_ov023_02260160[];
extern unsigned char data_ov023_02260194[];
extern unsigned char data_ov023_0226016c[];

void __sinit_ov023_02260020(void)
{
    *((unsigned char *) data_ov023_02260130 + 0x1) = *(unsigned char *) data_ov004_02256914;
    {
        int d[3];
        d[0] = 0x6000;
        d[1] = 0x0;
        d[2] = 0x3000;
        func_020b6468(data_ov023_02260178, 0x23, d, 0x23800000, (short) 0x0, 0x2, 0x2, (short) 0x0, 0x3);
        __register_global_object(data_ov023_02260178, (void *) func_020b649c, data_ov023_02260160);
    }
    {
        int d[3];
        d[0] = 0x1c000;
        d[1] = 0x0;
        d[2] = 0x3000;
        func_020b6468(data_ov023_02260194, 0x23, d, 0x23800000, (short) 0x0, 0x2, 0x2, (short) 0x0, 0x3);
        __register_global_object(data_ov023_02260194, (void *) func_020b649c, data_ov023_0226016c);
    }
}
