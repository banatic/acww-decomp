/* tv_5: 8 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02215c34 @ 0x02215c34, 0x3c bytes, Thumb
 * func_ov004_02215c0c @ 0x02215c0c, 0x28 bytes, Thumb
 * func_ov004_02215bd0 @ 0x02215bd0, 0x3c bytes, Thumb
 * func_ov004_02215ba8 @ 0x02215ba8, 0x28 bytes, Thumb
 * func_ov004_02215b8c @ 0x02215b8c, 0x1c bytes, Thumb
 * func_ov004_02215b68 @ 0x02215b68, 0x24 bytes, Thumb
 * func_ov004_02215b44 @ 0x02215b44, 0x24 bytes, Thumb
 * func_ov004_02215b18 @ 0x02215b18, 0x2c bytes, Thumb
 */

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_02215b44;

typedef struct {
    unsigned int unk_00;
    unsigned char pad_04[0xe8];
    unsigned int unk_EC;
} UnkStruct_02215b18;

extern int func_ov004_0220d208(void *, int, int, int);
extern void func_ov004_0220d280(void *, int, int);
extern int func_ov004_02210744(void *);
extern int func_ov004_02215d80(void *, int);
extern int func_ov004_0220d2a8(void *p);
extern int func_0205265c(void *p, int a, int b, int c);
extern int func_ov004_0221078c(void *);
extern int func_ov004_0221152c(unsigned int size);
extern void *func_ov004_02215f40(void *);
extern char data_ov004_02250f88;
extern char data_ov004_02251034;
extern void *func_ov004_02215e70(void *);
extern void func_ov004_02211518(void *self);

void *func_ov004_02215b68(void *this);

int func_ov004_02215c34(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_02210744(self);
    func_ov004_0220d208(self + 0x848, 0x0, 0x1, 0x0);
    func_ov004_0220d280(self + 0x740, 0x0, 0x0);
    func_ov004_02215d80(self, 0x0);
    return 0x1;
}

void func_ov004_02215c0c(char *self)
{
    if (func_ov004_0220d2a8(self + 0x740)) {
        func_0205265c(self, 1, 0xff, 1);
    }
}

int func_ov004_02215bd0(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0221078c(self);
    func_ov004_0220d208(self + 0x848, 0x1, 0x1, 0x0);
    func_ov004_0220d280(self + 0x740, 0x1, 0x0);
    func_ov004_02215d80(self, 0x1);
    return 0x1;
}

int func_ov004_02215ba8(char *self)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_ov004_0220d2a8((void *) (self + 0x740));
    if (v1 != 0x0) {
        return func_0205265c((void *) ((unsigned int) (self)), (int) (0x0), (int) (0xff), (int) (0x1));
    }
    return v1;
}

void func_ov004_02215b8c(void)
{
    void *conditionInput0;

    if ((conditionInput0 = (void *) (func_ov004_0221152c(0x868)))) {
        func_ov004_02215b68((void *) conditionInput0);
    }
}

void *func_ov004_02215b68(void *this)
{
    func_ov004_02215f40(this);
    *(void **) this = &data_ov004_02250f88;
    *(void **) ((char *) this + 0xec) = &data_ov004_02251034;
    return this;
}

void *func_ov004_02215b44(UnkStruct_02215b44 *obj)
{
    obj->unk_00 = ((int *) &data_ov004_02250f88);
    obj->unk_EC = ((int *) &data_ov004_02251034);
    func_ov004_02215e70(obj);
    return obj;
}

UnkStruct_02215b18 *func_ov004_02215b18(UnkStruct_02215b18 *self)
{
    self->unk_00 = (unsigned int) ((unsigned int *) &data_ov004_02250f88);
    self->unk_EC = (unsigned int) ((unsigned int *) &data_ov004_02251034);
    func_ov004_02215e70(self);
    func_ov004_02211518(self);
    return self;
}
