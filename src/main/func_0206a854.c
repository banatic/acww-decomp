/* func_0206a854 @ 0x0206a854, 0xa0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0206837c(void *ptr);
extern void *func_020ab550(void *ptr, int index);
extern void func_020ab5e4(void *ptr);
extern int func_020ab794(void *ptr);
extern int func_020ab798(void *ptr);
extern int func_020a855c(void *ptr, int a, int b, int c, int d, int e, int f);
extern void func_020a93e8(void *self, int value);
extern void func_020ab4bc(void *ptr, int index);
extern void func_020a9dc8(void *addr, void *ptr);
extern void func_020a9d24(void *addr);

typedef struct UnkStruct_0206a854 {
    unsigned char pad_00[0x24];
    void *unk_24;
    unsigned char pad_28[0x8];
    int unk_30;
    unsigned char pad_34[0x4];
    void *unk_38;
} UnkStruct_0206a854;

void func_0206a854(UnkStruct_0206a854 *self)
{
    void *varA;
    void *varB, *varC;
    void *varD;
    int varE, varF, varG, varH, varI, varJ;
    int result1;

    varA = func_0206837c(self->unk_24);
    varB = func_020ab550(varA, 0);
    varC = func_020ab550(varA, 1);
    varD = func_020ab550(varA, 2);

    func_020ab5e4(varA);

    varE = func_020ab794(varB);
    varF = func_020ab798(varB);
    varG = func_020ab794(varC);
    varH = func_020ab798(varC);
    varI = func_020ab794(varD);
    varJ = func_020ab798(varD);

    result1 = func_020a855c(&self->unk_38, varE, varF, varG, varH, varI, varJ);
    func_020a93e8(self, result1);

    func_020ab4bc(varA, 3);

    func_020a9dc8((char *) self->unk_24 + 0xb4, varA);
    func_020a9d24((char *) self->unk_24 + 0xb4);

    self->unk_30 = 5;
}
