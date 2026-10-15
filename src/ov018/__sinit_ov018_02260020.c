/* __sinit_ov018_02260020 @ 0x02260020, 0xac bytes, Thumb, module ov018
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b6468(void *out, unsigned char b, int *data, int v, short s1, unsigned char c1, unsigned char c2, short s2,
                          unsigned char c3);
extern void __register_global_object(void *a, void *b, void *node);

extern unsigned char data_ov018_02260164[];
extern void func_020b649c(void *object);
extern unsigned char data_ov018_02260140[];
extern unsigned char data_ov018_02260180[];
extern unsigned char data_ov018_0226014c[];
extern unsigned char data_ov018_0226019c[];
extern unsigned char data_ov018_02260158[];

void __sinit_ov018_02260020(void)
{
    {
        int d[3];
        d[0] = 0x0;
        d[1] = 0x0;
        d[2] = 0x0;
        func_020b6468(data_ov018_02260164, 0x3e, d, 0x800000, (short) 0x0, 0x3, 0x2, (short) 0x0, 0x0);
        __register_global_object(data_ov018_02260164, (void *) func_020b649c, data_ov018_02260140);
    }
    {
        int d[3];
        d[0] = 0x0;
        d[1] = 0x0;
        d[2] = 0x0;
        func_020b6468(data_ov018_02260180, 0x3f, d, 0x800000, (short) 0x0, 0x3, 0x2, (short) 0x0, 0x0);
        __register_global_object(data_ov018_02260180, (void *) func_020b649c, data_ov018_0226014c);
    }
    {
        int d[3];
        d[0] = 0x0;
        d[1] = 0x0;
        d[2] = 0x0;
        func_020b6468(data_ov018_0226019c, 0x3d, d, 0x800000, (short) 0x0, 0x2, 0x2, (short) 0x0, 0x0);
        __register_global_object(data_ov018_0226019c, (void *) func_020b649c, data_ov018_02260158);
    }
}
