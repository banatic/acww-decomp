/* __sinit_ov029_02260020 @ 0x02260020, 0x180 bytes, Thumb, module ov029
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b6468(void *out, unsigned char b, int *data, int v, short s1, unsigned char c1, unsigned char c2, short s2,
                          unsigned char c3);
extern void __register_global_object(void *a, void *b, void *node);

extern unsigned char data_ov004_02256914[];
extern unsigned char data_ov029_022601f8[];
extern unsigned char data_ov029_02260294[];
extern void func_020b649c(void);
extern unsigned char data_ov029_02260258[];
extern unsigned char data_ov029_022602b0[];
extern unsigned char data_ov029_02260270[];
extern unsigned char data_ov029_022602cc[];
extern unsigned char data_ov029_0226027c[];
extern unsigned char data_ov029_022602e8[];
extern unsigned char data_ov029_02260240[];
extern unsigned char data_ov029_02260304[];
extern unsigned char data_ov029_0226024c[];
extern unsigned char data_ov029_02260320[];
extern unsigned char data_ov029_02260264[];
extern unsigned char data_ov029_0226033c[];
extern unsigned char data_ov029_02260288[];

void __sinit_ov029_02260020(void)
{
    *((unsigned char *) data_ov029_022601f8 + 0x1) = *(unsigned char *) data_ov004_02256914;
    {
        int d[3];
        d[0] = 0x0;
        d[1] = 0x0;
        d[2] = 0x0;
        func_020b6468(data_ov029_02260294, 0x3c, d, 0x0, (short) 0x0, 0x2, 0x2, (short) 0x0, 0x4);
        __register_global_object(data_ov029_02260294, (void *) func_020b649c, data_ov029_02260258);
    }
    {
        int d[3];
        d[0] = 0x0;
        d[1] = 0x0;
        d[2] = 0x0;
        func_020b6468(data_ov029_022602b0, 0x3f, d, 0x0, (short) 0x0, 0x2, 0x2, (short) 0x0, 0x0);
        __register_global_object(data_ov029_022602b0, (void *) func_020b649c, data_ov029_02260270);
    }
    {
        int d[3];
        d[0] = 0x0;
        d[1] = 0x0;
        d[2] = 0x0;
        func_020b6468(data_ov029_022602cc, 0x3f, d, 0x800000, (short) 0x0, 0x2, 0x2, (short) 0x0, 0x0);
        __register_global_object(data_ov029_022602cc, (void *) func_020b649c, data_ov029_0226027c);
    }
    {
        int d[3];
        d[0] = 0x0;
        d[1] = 0x0;
        d[2] = 0x0;
        func_020b6468(data_ov029_022602e8, 0x3f, d, 0x800000, (short) 0x0, 0x2, 0x2, (short) 0x0, 0x0);
        __register_global_object(data_ov029_022602e8, (void *) func_020b649c, data_ov029_02260240);
    }
    {
        int d[3];
        d[0] = 0x0;
        d[1] = 0x0;
        d[2] = 0x0;
        func_020b6468(data_ov029_02260304, 0x3f, d, 0x800000, (short) 0x0, 0x2, 0x2, (short) 0x0, 0x0);
        __register_global_object(data_ov029_02260304, (void *) func_020b649c, data_ov029_0226024c);
    }
    {
        int d[3];
        d[0] = 0x0;
        d[1] = 0x0;
        d[2] = 0x0;
        func_020b6468(data_ov029_02260320, 0x3f, d, 0x800000, (short) 0x0, 0x2, 0x2, (short) 0x0, 0x0);
        __register_global_object(data_ov029_02260320, (void *) func_020b649c, data_ov029_02260264);
    }
    {
        int d[3];
        d[0] = 0x0;
        d[1] = 0x0;
        d[2] = 0x0;
        func_020b6468(data_ov029_0226033c, 0x3f, d, 0x800000, (short) 0x0, 0x2, 0x2, (short) 0x0, 0x0);
        __register_global_object(data_ov029_0226033c, (void *) func_020b649c, data_ov029_02260288);
    }
}
