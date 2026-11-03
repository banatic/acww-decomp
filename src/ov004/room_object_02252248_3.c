/* room_object_02252248_3: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02219730 @ 0x02219730, 0x1c bytes, Thumb
 * func_ov004_0221970c @ 0x0221970c, 0x24 bytes, Thumb
 * func_ov004_022196e8 @ 0x022196e8, 0x24 bytes, Thumb
 * func_ov004_022196bc @ 0x022196bc, 0x2c bytes, Thumb
 */

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_022196e8;

typedef struct {
    unsigned int unk_00;
    unsigned char pad_04[0xe8];
    unsigned int unk_EC;
} UnkStruct_022196bc;

extern int func_ov004_0221152c(unsigned int size);
extern void *func_ov004_022110e4(void *);
extern char data_ov004_02252248;
extern char data_ov004_022522f4;
extern void *func_ov004_02210cf0(void *);
extern void func_ov004_02211518(void *self);

void *func_ov004_0221970c(void *this);

void func_ov004_02219730(void)
{
    void *conditionInput0;

    if ((conditionInput0 = (void *) (func_ov004_0221152c(0x848)))) {
        func_ov004_0221970c((void *) conditionInput0);
    }
}

void *func_ov004_0221970c(void *this)
{
    func_ov004_022110e4(this);
    *(void **) this = &data_ov004_02252248;
    *(void **) ((char *) this + 0xec) = &data_ov004_022522f4;
    return this;
}

void *func_ov004_022196e8(UnkStruct_022196e8 *obj)
{
    obj->unk_00 = ((int *) &data_ov004_02252248);
    obj->unk_EC = ((int *) &data_ov004_022522f4);
    func_ov004_02210cf0(obj);
    return obj;
}

UnkStruct_022196bc *func_ov004_022196bc(UnkStruct_022196bc *self)
{
    self->unk_00 = (unsigned int) ((unsigned int *) &data_ov004_02252248);
    self->unk_EC = (unsigned int) ((unsigned int *) &data_ov004_022522f4);
    func_ov004_02210cf0(self);
    func_ov004_02211518(self);
    return self;
}
