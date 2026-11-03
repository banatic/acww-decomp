/* room_object_022518e8_3: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0221934c @ 0x0221934c, 0x1c bytes, Thumb
 * func_ov004_02219328 @ 0x02219328, 0x24 bytes, Thumb
 * func_ov004_02219304 @ 0x02219304, 0x24 bytes, Thumb
 * func_ov004_022192d8 @ 0x022192d8, 0x2c bytes, Thumb
 */

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_02219304;

typedef struct {
    unsigned int unk_00;
    unsigned char pad_04[0xe8];
    unsigned int unk_EC;
} UnkStruct_022192d8;

extern int func_ov004_0221152c(unsigned int size);
extern void *func_ov004_022110e4(void *);
extern char data_ov004_022518e8;
extern char data_ov004_02251994;
extern void *func_ov004_02210cf0(void *);
extern void func_ov004_02211518(void *self);

void *func_ov004_02219328(void *this);

void func_ov004_0221934c(void)
{
    void *conditionInput0;

    if ((conditionInput0 = (void *) (func_ov004_0221152c(0x848)))) {
        func_ov004_02219328((void *) conditionInput0);
    }
}

void *func_ov004_02219328(void *this)
{
    func_ov004_022110e4(this);
    *(void **) this = &data_ov004_022518e8;
    *(void **) ((char *) this + 0xec) = &data_ov004_02251994;
    return this;
}

void *func_ov004_02219304(UnkStruct_02219304 *obj)
{
    obj->unk_00 = ((int *) &data_ov004_022518e8);
    obj->unk_EC = ((int *) &data_ov004_02251994);
    func_ov004_02210cf0(obj);
    return obj;
}

UnkStruct_022192d8 *func_ov004_022192d8(UnkStruct_022192d8 *self)
{
    self->unk_00 = (unsigned int) ((unsigned int *) &data_ov004_022518e8);
    self->unk_EC = (unsigned int) ((unsigned int *) &data_ov004_02251994);
    func_ov004_02210cf0(self);
    func_ov004_02211518(self);
    return self;
}
