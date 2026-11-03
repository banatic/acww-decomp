/* letter_storage_6: 4 functions, module ov105
 * mwccarm 1.2/base -O4,s
 * func_ov105_0229da7c @ 0x0229da7c, 0x20 bytes, Thumb
 * func_ov105_0229d9e0 @ 0x0229d9e0, 0x9c bytes, Thumb
 * func_ov105_0229d970 @ 0x0229d970, 0x70 bytes, Thumb
 * func_ov105_0229d908 @ 0x0229d908, 0x68 bytes, Thumb
 */

typedef struct UnkStruct_0229d908 UnkStruct_0229d908;

struct UnkStruct_0229d908 {
    unsigned char pad_00[0x2b4];
    unsigned char unk_2B4;
    unsigned char pad_2B5[0x2b7 - 0x2b5];
    unsigned char unk_2B7;
    unsigned char unk_2B8;
    unsigned char unk_2B9;
    unsigned char pad_2BA[0x2bd - 0x2ba];
    unsigned char unk_2BD;
    unsigned char pad_2BE[0x2c0 - 0x2be];
    unsigned char unk_2C0;
    unsigned char pad_2C1[0x23bc - 0x2c1];
    unsigned char unk_23BC;
};

extern int func_0206fe60(void);
extern void func_ov105_0229dafc(int);
extern void func_ov105_0229da9c(int);
extern unsigned char *func_ov002_02208098(void *self, unsigned char value);
extern int func_ov105_0229d530(void *self, unsigned char b);
extern int func_ov105_0229d4c4(void *self, unsigned char b);
extern void func_ov002_02207cf8(void *p);
extern void func_ov002_02207d00(void *p);
extern int func_ov105_0229d468(void *self, int x);
extern void func_ov105_0229c320(void *self, int x);
extern void func_ov105_0229c330(void *self, int x);
extern void func_ov094_022999cc(void);
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern int func_ov002_02207d24(void *, int);
extern void func_ov105_0229d0f8(void *, unsigned char);
extern void func_ov105_0229d1c4(void *);
extern void func_ov094_022999c0(void);
extern void func_ov105_0229d17c(UnkStruct_0229d908 *self);

void func_ov105_0229da7c(int r0)
{
    int r4 = r0;
    if (func_0206fe60() != 0) {
        func_ov105_0229dafc(r4);
    } else {
        func_ov105_0229da9c(r4);
    }
}

void func_ov105_0229d9e0(char *self, int a1)
{
    *((unsigned char *) (self + 0x2b5)) = a1;
    func_ov002_02208098(self, 1);
    {
        unsigned char va = data_021f6c58;
        unsigned char vb = data_021f6c54;
        *((int *) (self + 0xa4)) = func_ov105_0229d530(self, *((unsigned char *) (self + 0x2b5))) - va;
        *((int *) (self + 0xa8)) = func_ov105_0229d4c4(self, *((unsigned char *) (self + 0x2b5))) - vb;
    }
    *((unsigned char *) (self + 0x2b6)) = a1;
    func_ov002_02207cf8(self + 0x23bc);
    func_ov002_02207d00(self + 0x23bc);
    *((unsigned char *) (self + 0x2c3)) = 2;
    if (func_ov105_0229d468(self, a1) != 0) {
        func_ov105_0229c320(self, 4);
    } else {
        func_ov105_0229c330(self, 4);
        func_ov094_022999cc();
    }
}

void func_ov105_0229d970(unsigned char *self, unsigned char arg1)
{
    func_ov105_0229c330(self, 0x1000);
    self[0x2b7] = arg1;
    self[0x2b9] = arg1;
    self[0x2b8] = self[0x2c0];
    func_ov002_02207d24(self + 0x23bc, 1);
    func_ov105_0229d0f8(self, arg1);
    if (self[0x2b4] == 1) {
        func_ov002_02208098(self, 4);
    }
    func_ov105_0229d1c4(self);
    func_ov094_022999c0();
}

void func_ov105_0229d908(UnkStruct_0229d908 *self, unsigned char value)
{
    self->unk_2B7 = value;
    self->unk_2B9 = value;
    self->unk_2B8 = self->unk_2C0;
    func_ov002_02207d24(&self->unk_23BC, 1);
    func_ov105_0229d0f8((void *) self, value);
    if (self->unk_2B4 == 1) {
        self->unk_2BD = 8;
    }
    func_ov105_0229d17c(self);
    func_ov094_022999c0();
}
