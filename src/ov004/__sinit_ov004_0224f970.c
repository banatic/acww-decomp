/* __sinit_ov004_0224f970 @ 0x0224f970, 0xd4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b6468(void *out, unsigned char b, int *data, int v, short s1, unsigned char c1, unsigned char c2, short s2,
                          unsigned char c3);
extern void __register_global_object(void *a, void *destructor, void *node);
extern void func_020b649c(void *arg0);

extern unsigned char data_ov004_0225ff7c[];
extern unsigned char data_ov004_0225ff70[];
extern unsigned char data_ov004_0225ff98[];
extern unsigned char data_ov004_0225ff64[];
extern unsigned char data_ov004_0225ffb4[];
extern unsigned char data_ov004_0225ff58[];

#pragma define_section INIT ".init" RX
#pragma section INIT begin

void __sinit_ov004_0224f970(void)
{
    {
        int d1[3];
        d1[0] = 0xf000;
        d1[1] = 0x200;
        d1[2] = 0x1d000;
        func_020b6468(data_ov004_0225ff7c, 1, d1, 0x11000000, 0x4000, 2, 2, (short) 0xffffc000, 2);
        __register_global_object(data_ov004_0225ff7c, ((void *) &func_020b649c), data_ov004_0225ff70);
    }
    {
        int d2[3];
        d2[0] = 0x11000;
        d2[1] = 0x200;
        d2[2] = 0x1d000;
        func_020b6468(data_ov004_0225ff98, 5, d2, 0x11000000, (short) 0xffffc000, 2, 2, 0x4000, 2);
        __register_global_object(data_ov004_0225ff98, ((void *) &func_020b649c), data_ov004_0225ff64);
    }
    {
        int d3[3];
        d3[0] = 0;
        d3[1] = 0;
        d3[2] = 0;
        func_020b6468(data_ov004_0225ffb4, 0x3e, d3, 0x00800000, 0, 2, 2, 0, 0);
        __register_global_object(data_ov004_0225ffb4, ((void *) &func_020b649c), data_ov004_0225ff58);
    }
}

#pragma section INIT end
