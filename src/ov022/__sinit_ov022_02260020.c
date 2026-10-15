/* __sinit_ov022_02260020 @ 0x02260020, 0xec bytes, Thumb, module ov022
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b6468(void *out, unsigned char b, int *data, int v, short s1, unsigned char c1, unsigned char c2, short s2,
                          unsigned char c3);
extern void __register_global_object(void *a, void *b, void *node);

extern unsigned char data_ov004_02256914[];
extern unsigned char data_ov022_02260170[];
extern unsigned char data_ov022_022601c4[];
extern void func_020b649c(void *object);
extern unsigned char data_ov022_022601a0[];
extern unsigned char data_ov022_022601e0[];
extern unsigned char data_ov022_022601ac[];
extern unsigned char data_ov022_022601fc[];
extern unsigned char data_ov022_022601b8[];

void __sinit_ov022_02260020(void)
{
    *((unsigned char *) data_ov022_02260170 + 0x1) = *(unsigned char *) data_ov004_02256914;
    {
        int d[3];
        d[0] = 0x17000;
        d[1] = 0x0;
        d[2] = 0x1a000;
        func_020b6468(data_ov022_022601c4, 0x20, d, 0x23800000, (short) 0xc000, 0x2, 0x2, (short) 0xc000, 0x3);
        __register_global_object(data_ov022_022601c4, (void *) func_020b649c, data_ov022_022601a0);
    }
    {
        int d[3];
        d[0] = 0x6000;
        d[1] = 0x0;
        d[2] = 0x1d000;
        func_020b6468(data_ov022_022601e0, 0x24, d, 0x23800000, (short) 0x8000, 0x2, 0x2, (short) 0x8000, 0x3);
        __register_global_object(data_ov022_022601e0, (void *) func_020b649c, data_ov022_022601ac);
    }
    {
        int d[3];
        d[0] = 0x1c000;
        d[1] = 0x0;
        d[2] = 0x1d000;
        func_020b6468(data_ov022_022601fc, 0x24, d, 0x23800000, (short) 0x8000, 0x2, 0x2, (short) 0x8000, 0x3);
        __register_global_object(data_ov022_022601fc, (void *) func_020b649c, data_ov022_022601b8);
    }
}
