/* func_ov068_022732bc @ 0x022732bc, 0x7c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0222c3c4(void *p, int v);
extern int func_ov004_0222c3b4(void *p, int v);
extern void func_02055060(void *p, int a, void *b, int c, int d, int e);
extern int func_02055e00(void *p);
extern void func_02056440(void *p, int a, int b, void *c, int d, int e);

typedef struct UnkStruct_022732bc {
    char pad_00[0xec];
    char unk_EC[0xa4];
    unsigned int unk_190;
    char pad_194[0x10];
    char unk_1A4[1];
    char pad_1A5[0x290 - 0x1a5];
    char unk_290[1];
    char pad_291[0x298 - 0x291];
    unsigned int unk_298;
} UnkStruct_022732bc;

void func_ov068_022732bc(UnkStruct_022732bc *self, void *r4)
{
    int tmp1, tmp2, tmp3;
    unsigned int local0, local1;

    tmp1 = func_ov004_0222c3c4(&self->unk_1A4, 0);
    local0 = (self->unk_190 << 4) >> 16;
    local1 = 0;
    func_02055060(&self->unk_EC, tmp1, r4, 0x1000, local0, local1);

    tmp2 = func_02055e00(&self->unk_EC);
    tmp3 = func_ov004_0222c3b4(&self->unk_1A4, 0);
    local0 = 0x1000;
    local1 = (self->unk_298 << 4) >> 16;
    func_02056440(&self->unk_290, tmp2, tmp3, r4, local0, local1);
}
