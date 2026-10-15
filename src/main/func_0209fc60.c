/* func_0209fc60 @ 0x0209fc60, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f3c18;
extern char data_021f3cbc[];
extern void func_0203f5e0(void *);
extern void MI_CpuCopy8(void *, void *, int);
extern void *func_0203f5d8(void *);
extern void MI_CpuFill8(void *, int, int);
extern int func_02000b7c(void);
extern void DGT_Hash1CalcHmac(void *, void *, int, int, int);
extern int func_02064344(void *, void *, int);
extern int func_0203f5a4(void *);
extern void func_0203f5dc(void *);

void func_0209fc60(void)
{
    char buf1[0x10];
    char buf2[0xd2];

    if (data_021f3c18) {
        data_021f3c18 = 0;
        func_0203f5e0(buf2);
        MI_CpuCopy8(data_021f3cbc, buf2, 0xd2);
        MI_CpuFill8(func_0203f5d8(buf2), 0, 0x10);
        DGT_Hash1CalcHmac(buf1, buf2, 0xd2, func_02000b7c(), 0x10);
        if (func_02064344(func_0203f5d8(data_021f3cbc), buf1, 0x10) == 0) {
            func_0203f5a4(data_021f3cbc);
        }
        MI_CpuFill8(data_021f3cbc, 0, 0xd2);
        func_0203f5dc(buf2);
    }
}
