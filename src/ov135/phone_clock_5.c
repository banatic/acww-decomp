/* phone_clock_5: 4 functions, module ov135
 * mwccarm 1.2/base -O4,s
 * func_ov135_0229d4b8 @ 0x0229d4b8, 0x44 bytes, Thumb
 * func_ov135_0229d498 @ 0x0229d498, 0x1e bytes, Thumb
 * func_ov135_0229d47c @ 0x0229d47c, 0x1a bytes, Thumb
 * func_ov135_0229d428 @ 0x0229d428, 0x54 bytes, Thumb
 */

typedef struct UnkStruct_0229d498 {
    unsigned char pad_00[0x8c];
    unsigned char unk_8C;
} UnkStruct_0229d498;

extern void *func_ov002_02207f80(int size);
extern void *func_ov002_0220830c(void *argument0);
extern void *func_ov002_02209ccc(void *p);
extern void *func_ov002_0220b008(void *p);
extern void *func_ov134_0229bed4(void *p);
extern int data_ov135_0229d610;
extern void func_ov135_0229d0e8(void *self);
extern unsigned char *func_ov002_022080a0(void *, unsigned char);
extern int func_020ee45c(int a);
extern void func_ov092_0229929c(int a);
extern void func_ov135_0229d0c8(int a);
extern int func_0206fe54(void);
extern void func_ov002_02209eb8(char *p);
extern int func_ov135_0229c574(char *p, int flag);
extern int func_ov002_02207f60(char *p);
extern void func_ov134_0229b220(char *p, int a, int b);
extern void func_ov002_0220ad18(char *p, int b);

void *func_ov135_0229d4b8(void)
{
    void *r4;
    r4 = func_ov002_02207f80(0x2b78);
    if (r4 != 0) {
        func_ov002_0220830c(r4);
        *(unsigned int *) r4 = (unsigned int) &data_ov135_0229d610;
        func_ov002_02209ccc((void *) ((unsigned int) r4 + 0x98));
        func_ov002_0220b008((void *) ((unsigned int) r4 + 0xFC));
        func_ov134_0229bed4((void *) ((unsigned int) r4 + 0x2C8));
    }
    return r4;
}

int func_ov135_0229d498(UnkStruct_0229d498 *self)
{
    func_ov135_0229d0e8(self);
    self->unk_8C = 0;
    func_ov002_022080a0(self, 0);
    return 1;
}

int func_ov135_0229d47c(int a)
{
    int saved = a;
    int ret;

    ret = func_020ee45c(a);
    func_ov092_0229929c(ret);
    func_ov135_0229d0c8(saved);

    return 1;
}

int func_ov135_0229d428(char *self)
{
    int a;
    int b;

    if (func_0206fe54() != 0) {
        func_ov002_02209eb8(self + 0x98);
    }
    if (func_ov135_0229c574(self, 1) == 0) {
        return 0;
    }
    a = func_ov002_02207f60(self);
    func_ov134_0229b220(self + 0x2c8, 0, a);
    b = func_ov002_02207f60(self);
    func_ov002_0220ad18(self + 0xfc, b);
    return 1;
}
