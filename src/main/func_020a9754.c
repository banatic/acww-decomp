/* func_020a9754 @ 0x020a9754, 0xd8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02064658(void *dst, const void *src, int size, int flag);
extern int func_020a9ae8(void *addr);
extern int func_020a9ae4(void *addr);
extern int func_020a9ae0(void *addr);
extern int func_020a9adc(void *addr);

struct GStruct {
    int unk_00;
    int unk_04;
    unsigned short unk_08;
    unsigned short unk_0A;
    unsigned short unk_0C;
    unsigned char unk_0E;
    unsigned char pad_0F[5];
};

extern struct GStruct data_021f4458;
extern unsigned char data_021f445c;
extern unsigned char data_021f4460;
extern unsigned char data_021f4462;
extern unsigned char data_021f4464;
extern unsigned char data_021f4466;

int func_020a9754(unsigned char *p)
{
    int cond1, cond2, cond3, cond4;
    unsigned short fs;

    func_02064658(p + 0x44, (const void *) &data_021f4458, 0x14, 0x20);

    data_021f4458.unk_00 = func_020a9ae8((void *) &data_021f4458);
    data_021f4458.unk_04 = func_020a9ae4((void *) &data_021f445c);
    data_021f4458.unk_08 = func_020a9ae0((void *) &data_021f4460);
    data_021f4458.unk_0A = func_020a9ae0((void *) &data_021f4462);
    data_021f4458.unk_0C = func_020a9ae0((void *) &data_021f4464);
    data_021f4458.unk_0E = func_020a9adc((void *) &data_021f4466);

    cond1 = (data_021f4458.unk_00 == 0x494e4631);
    fs = data_021f4458.unk_08;
    cond2 = 0;
    if (fs <= 0x100) {
        if (p[0x8d] < fs) {
            cond2 = 1;
        }
    }
    cond3 = (data_021f4458.unk_0A == (p[4] != 0 ? 0xc : 4));
    cond4 = (data_021f4458.unk_0C == 0);

    if (cond1 && cond2 && cond3 && cond4) {
        return 1;
    }
    return 0;
}
