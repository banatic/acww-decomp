/* func_0209fcd8 @ 0x0209fcd8, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f3c04;
extern unsigned char data_021f3d90[];

extern void func_0203f674(unsigned char *);
extern void MI_CpuCopy8(unsigned char *, const unsigned char *, unsigned int);
extern unsigned char *func_0203f658(unsigned char *);
extern void MI_CpuFill8(unsigned char *, int, unsigned int);
extern int func_02000b7c(void);
extern void DGT_Hash1CalcHmac(unsigned char *, const unsigned char *, unsigned int, int, int);
extern int func_02064344(unsigned char *, unsigned char *, unsigned int);
extern void func_0203f5e4(unsigned char *);
extern void func_0203f664(unsigned char *);

void func_0209fcd8(void)
{
    if (data_021f3c04) {
        unsigned char small[0x10];
        unsigned char buf[0x114];

        data_021f3c04 = 0;
        func_0203f674(buf);
        MI_CpuCopy8(data_021f3d90, buf, 0x114);
        MI_CpuFill8(func_0203f658(buf), 0, 0x10);
        DGT_Hash1CalcHmac(small, buf, 0x114, func_02000b7c(), 0x10);
        if (func_02064344(func_0203f658(data_021f3d90), small, 0x10) == 0) {
            func_0203f5e4(data_021f3d90);
        }
        MI_CpuFill8(data_021f3d90, 0, 0x114);
        func_0203f664(buf);
    }
}
