/* func_ov135_0229c97c @ 0x0229c97c, 0xa0 bytes, Thumb, module ov135
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a720(unsigned char *, int);
extern void func_ov002_02208090(unsigned char *, int);
extern void func_ov002_02208098(unsigned char *, int);
extern void func_0206fc4c(int);
extern void func_ov134_0229bbdc(unsigned char *, unsigned char *);
extern void func_0206f820(unsigned char *);
extern int func_ov134_0229bbbc(unsigned char *);
extern void func_0206f780(void);
extern void func_0206f774(void);
extern void MI_CpuCopy8(unsigned char *, unsigned char *, int);
extern int func_0209db78(unsigned char *, unsigned char *);
extern int func_0209db50(unsigned char *, unsigned char *);
extern void func_0209dfc0(void);

extern unsigned char data_021dc7a8[];

void func_ov135_0229c97c(unsigned char *self)
{
    unsigned char key[8];
    unsigned char buf1[8];
    unsigned char buf2[8];
    unsigned char *base;
    int res1;
    int res2;

    func_ov002_0220a720(self + 0xfc, 6);
    func_ov002_02208090(self, 2);
    func_ov002_02208098(self, 0xd);
    func_0206fc4c(1);

    *(unsigned int *) key = 0;
    *(unsigned int *) (key + 4) = 0;

    func_ov134_0229bbdc(self + 0x2c8, key);
    func_0206f820(key);

    base = data_021dc7a8;

    if (func_ov134_0229bbbc(self + 0x2c8)) {
        func_0206f780();
    } else {
        func_0206f774();
    }

    MI_CpuCopy8(key, buf1, 8);
    res1 = func_0209db78(base + 0x173cc, buf1);

    MI_CpuCopy8(key, buf2, 8);
    res2 = func_0209db50(base + 0x173cc, buf2);

    *(int *) (base + 0x173cc) = res1;
    *(short *) (base + 0x173d0) = (short) res2;

    func_0209dfc0();
}
