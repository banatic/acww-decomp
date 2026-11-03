/* wfc_session: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209fd54 @ 0x0209fd54, 0x58 bytes, Thumb
 * func_0209fcd8 @ 0x0209fcd8, 0x7c bytes, Thumb
 * func_0209fc60 @ 0x0209fc60, 0x78 bytes, Thumb
 */

extern unsigned char data_021f3c14;
extern struct B data_021f40a4;
extern struct C data_021f3278;
extern int func_02050920(struct B *, int);
extern void func_02088214(struct B *, int);
extern void MI_CpuCopy8(struct B *, struct C *, int);
extern void MI_CpuFill8(struct B *, int, int);
extern void func_020881b8(struct B *, int);
extern unsigned char data_021f3c04;
extern unsigned char data_021f3d90[];
extern int func_0203f674(unsigned char *);
extern unsigned char *func_0203f658(unsigned char *);
extern int func_02000b7c(void);
extern void DGT_Hash1CalcHmac(unsigned char *, const unsigned char *, unsigned int, int, int);
extern int func_02064344(unsigned char *, unsigned char *, unsigned int);
extern int func_0203f5e4(unsigned char *);
extern int func_0203f664(unsigned char *);
extern unsigned char data_021f3c18;
extern char data_021f3cbc[];
extern void func_0203f5e0(void *);
extern void *func_0203f5d8(void *);
extern int func_0203f5a4(void *);
extern void func_0203f5dc(void *);

void func_0209fd54(void)
{
    int result;
    struct C *pC;

    if (data_021f3c14 == 0) {
        return;
    }
    data_021f3c14 = 0;
    result = func_02050920(&data_021f40a4, 0x238);
    pC = &data_021f3278;
    if (result == 0) {
        func_02088214(&data_021f40a4, 1);
        MI_CpuCopy8(&data_021f40a4, pC, 0x238);
    }
    MI_CpuFill8(&data_021f40a4, 0, 0x238);
    func_020881b8(&data_021f40a4, 1);
}

void func_0209fcd8(void)
{
    if (data_021f3c04) {
        unsigned char small[0x10];
        unsigned char buf[0x114];

        data_021f3c04 = 0;
        func_0203f674(buf);
        MI_CpuCopy8((struct B *) data_021f3d90, (struct C *) buf, 0x114);
        MI_CpuFill8((struct B *) (func_0203f658(buf)), 0, 0x10);
        DGT_Hash1CalcHmac(small, buf, 0x114, func_02000b7c(), 0x10);
        if (func_02064344(func_0203f658(data_021f3d90), small, 0x10) == 0) {
            func_0203f5e4(data_021f3d90);
        }
        MI_CpuFill8((struct B *) data_021f3d90, 0, 0x114);
        func_0203f664(buf);
    }
}

void func_0209fc60(void)
{
    char buf1[0x10];
    char buf2[0xd2];

    if (data_021f3c18) {
        data_021f3c18 = 0;
        func_0203f5e0(buf2);
        MI_CpuCopy8((struct B *) data_021f3cbc, (struct C *) buf2, 0xd2);
        MI_CpuFill8((struct B *) (func_0203f5d8(buf2)), 0, 0x10);
        DGT_Hash1CalcHmac((unsigned char *) buf1, (const unsigned char *) buf2, 0xd2, func_02000b7c(), 0x10);
        if (func_02064344((unsigned char *) (func_0203f5d8(data_021f3cbc)), (unsigned char *) buf1, 0x10) == 0) {
            func_0203f5a4(data_021f3cbc);
        }
        MI_CpuFill8((struct B *) data_021f3cbc, 0, 0xd2);
        func_0203f5dc(buf2);
    }
}
