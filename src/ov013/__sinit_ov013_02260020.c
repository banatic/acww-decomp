/* __sinit_ov013_02260020 @ 0x02260020, 0x68 bytes, Thumb, module ov013
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b6468(void *out, unsigned char b, int *data, int v, short s1, unsigned char c1, unsigned char c2, short s2,
                          unsigned char c3);
extern void __register_global_object(void *a, void *b, void *node);

extern unsigned char data_ov004_02256914[];
extern unsigned char data_ov013_022600d0[];
extern unsigned char data_ov013_0226014c[];
extern void func_020b649c(void *object);
extern unsigned char data_ov013_02260140[];

#pragma define_section INIT ".init" RX
#pragma section INIT begin

void __sinit_ov013_02260020(void)
{
    *((unsigned char *) data_ov013_022600d0 + 0x1) = *(unsigned char *) data_ov004_02256914;
    {
        int d[3];
        d[0] = 0xa000;
        d[1] = 0x200;
        d[2] = 0x9000;
        func_020b6468(data_ov013_0226014c, 0x1d, d, 0x23800000, (short) 0x0, 0x2, 0x2, (short) 0x0, 0x3);
        __register_global_object(data_ov013_0226014c, (void *) func_020b649c, data_ov013_02260140);
    }
}

#pragma section INIT end
