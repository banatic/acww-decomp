/* bank_amount_7: 4 functions, module ov131
 * mwccarm 1.2/base -O4,s
 * func_ov131_0229b820 @ 0x0229b820, 0x44 bytes, Thumb
 * func_ov131_0229b800 @ 0x0229b800, 0x1e bytes, Thumb
 * func_ov131_0229b7e4 @ 0x0229b7e4, 0x1a bytes, Thumb
 * func_ov131_0229b794 @ 0x0229b794, 0x50 bytes, Thumb
 */

struct UnkStruct_0229b820 {
    void *meta;
    char pad_04[0x90];
    char sub_94[0x64];
    char sub_f8[0x1cc];
    char sub_2c4[4];
};

typedef struct SelfType {
    unsigned char pad_00[0x8c];
    unsigned char flag;
} SelfType;

extern void *func_ov002_02207f80(int);
extern void *func_ov002_0220830c(void *argument0);
extern void *func_ov002_02209ccc(char *);
extern void *func_ov002_0220b008(char *);
extern void *func_ov130_0229a7ac(char *);
extern int data_ov131_0229b8f0;
extern void func_ov131_0229b4cc(SelfType *self);
extern unsigned char *func_ov002_022080a0(void *, unsigned char);
extern int func_020ee45c(int);
extern void func_ov092_0229929c(int);
extern void func_ov131_0229b4b0(int);
extern int func_0206fe54(void);
extern void func_ov002_02209eb8(char *);
extern int func_ov131_0229ad44(void *, int);
extern int func_ov002_02207f60(void *);
extern void func_ov002_0220ad18(char *, int);
extern void func_ov130_02299de8(char *, int);

struct UnkStruct_0229b820 *func_ov131_0229b820(void)
{
    struct UnkStruct_0229b820 *self = func_ov002_02207f80(0x1558);
    if (self != 0) {
        func_ov002_0220830c(self);
        self->meta = (void *) &data_ov131_0229b8f0;
        func_ov002_02209ccc(self->sub_94);
        func_ov002_0220b008(self->sub_f8);
        func_ov130_0229a7ac(self->sub_2c4);
    }
    return self;
}

int func_ov131_0229b800(SelfType *self)
{
    func_ov131_0229b4cc(self);
    self->flag = 0;
    func_ov002_022080a0(self, 0);
    return 1;
}

int func_ov131_0229b7e4(int arg)
{
    func_ov092_0229929c(func_020ee45c(arg));
    func_ov131_0229b4b0(arg);
    return 1;
}

int func_ov131_0229b794(void *param0)
{
    if (func_0206fe54()) {
        func_ov002_02209eb8((char *) param0 + 0x94);
    }
    if (!func_ov131_0229ad44(param0, 1)) {
        return 0;
    } else {
        int tmp1;
        int tmp2;
        tmp1 = func_ov002_02207f60(param0);
        func_ov002_0220ad18((char *) param0 + 0xf8, tmp1);
        tmp2 = func_ov002_02207f60(param0);
        func_ov130_02299de8((char *) param0 + 0x2c4, tmp2);
        return 1;
    }
}
