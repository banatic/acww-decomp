/* telephone_6: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02211c64 @ 0x02211c64, 0x1c bytes, Thumb
 * func_ov004_02211c40 @ 0x02211c40, 0x24 bytes, Thumb
 * func_ov004_02211c1c @ 0x02211c1c, 0x24 bytes, Thumb
 * func_ov004_02211bf0 @ 0x02211bf0, 0x2c bytes, Thumb
 */

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_02211c1c;

typedef struct {
    unsigned int unk_00;
    unsigned char pad_04[0xe8];
    unsigned int unk_EC;
} UnkStruct_02211bf0;

extern int func_ov004_0221152c(unsigned int size);
extern void *func_ov004_022110e4(void *);
extern char data_ov004_02252950;
extern char data_ov004_022529fc;
extern void *func_ov004_02210cf0(void *);
extern void func_ov004_02211518(void *self);

void *func_ov004_02211c40(void *this);

void func_ov004_02211c64(void)
{
    void *conditionInput0;

    if ((conditionInput0 = (void *) (func_ov004_0221152c(0x85c)))) {
        func_ov004_02211c40((void *) conditionInput0);
    }
}

void *func_ov004_02211c40(void *this)
{
    func_ov004_022110e4(this);
    *(void **) this = &data_ov004_02252950;
    *(void **) ((char *) this + 0xec) = &data_ov004_022529fc;
    return this;
}

void *func_ov004_02211c1c(UnkStruct_02211c1c *obj)
{
    obj->unk_00 = ((int *) &data_ov004_02252950);
    obj->unk_EC = ((int *) &data_ov004_022529fc);
    func_ov004_02210cf0(obj);
    return obj;
}

UnkStruct_02211bf0 *func_ov004_02211bf0(UnkStruct_02211bf0 *self)
{
    self->unk_00 = (unsigned int) ((unsigned int *) &data_ov004_02252950);
    self->unk_EC = (unsigned int) ((unsigned int *) &data_ov004_022529fc);
    func_ov004_02210cf0(self);
    func_ov004_02211518(self);
    return self;
}
