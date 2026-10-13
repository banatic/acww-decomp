/* func_02041f6c @ 0x02041f6c, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MIi_CpuClear16(unsigned short, void *, int);
extern unsigned char data_021c75e8;
extern unsigned int data_021c75b4;
extern void func_02041fe0(void);
extern unsigned char data_021c75cc;
extern void func_02042154(void);
extern void func_02042120(void);
extern int func_0205c024(void *, void (*)(void), void (*)(void), int);
extern unsigned char data_021c75ac;
struct g21c75b8_type {
    unsigned char pad_00[4];
    unsigned int unk_04;
};
extern struct g21c75b8_type data_021c75b8;
extern void func_02001aac(int);

void func_02041f6c(void)
{
    volatile unsigned short local = 0;
    MIi_CpuClear16(local, (void *) &data_021c75e8, 0x180);
    data_021c75b4 = (unsigned int) &data_021c75e8;
    func_02041fe0();
    if (func_0205c024((void *) &data_021c75cc, func_02042154, func_02042120, 0) != 0) {
        data_021c75ac |= 1;
    }
    if (data_021c75b8.unk_04 == 0x1000) {
        func_02001aac(0);
    }
}
