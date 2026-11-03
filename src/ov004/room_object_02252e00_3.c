/* room_object_02252e00_3: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0221a134 @ 0x0221a134, 0x1c bytes, Thumb
 * func_ov004_0221a110 @ 0x0221a110, 0x24 bytes, Thumb
 * func_ov004_0221a0ec @ 0x0221a0ec, 0x24 bytes, Thumb
 * func_ov004_0221a0c0 @ 0x0221a0c0, 0x2c bytes, Thumb
 */

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_0221a0ec;

typedef struct {
    unsigned int unk_00;
    unsigned char pad_04[0xe8];
    unsigned int unk_EC;
} UnkStruct_0221a0c0;

extern int func_ov004_0221152c(unsigned int size);
extern void *func_ov004_022110e4(void *);
extern char data_ov004_02252e00;
extern char data_ov004_02252eac;
extern void *func_ov004_02210cf0(void *);
extern void func_ov004_02211518(void *self);

void *func_ov004_0221a110(void *this);

void func_ov004_0221a134(void)
{
    void *conditionInput0;

    if ((conditionInput0 = (void *) (func_ov004_0221152c(0x848)))) {
        func_ov004_0221a110((void *) conditionInput0);
    }
}

void *func_ov004_0221a110(void *this)
{
    func_ov004_022110e4(this);
    *(void **) this = &data_ov004_02252e00;
    *(void **) ((char *) this + 0xec) = &data_ov004_02252eac;
    return this;
}

void *func_ov004_0221a0ec(UnkStruct_0221a0ec *obj)
{
    obj->unk_00 = ((int *) &data_ov004_02252e00);
    obj->unk_EC = ((int *) &data_ov004_02252eac);
    func_ov004_02210cf0(obj);
    return obj;
}

UnkStruct_0221a0c0 *func_ov004_0221a0c0(UnkStruct_0221a0c0 *self)
{
    self->unk_00 = (unsigned int) ((unsigned int *) &data_ov004_02252e00);
    self->unk_EC = (unsigned int) ((unsigned int *) &data_ov004_02252eac);
    func_ov004_02210cf0(self);
    func_ov004_02211518(self);
    return self;
}
