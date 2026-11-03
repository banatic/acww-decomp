/* room_object_022524a0_4: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02214458 @ 0x02214458, 0x1c bytes, Thumb
 * func_ov004_02214434 @ 0x02214434, 0x24 bytes, Thumb
 * func_ov004_02214410 @ 0x02214410, 0x24 bytes, Thumb
 * func_ov004_022143e4 @ 0x022143e4, 0x2c bytes, Thumb
 */

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_02214410;

typedef struct {
    unsigned int unk_00;
    unsigned char pad_04[0xe8];
    unsigned int unk_EC;
} UnkStruct_022143e4;

extern int func_ov004_0221152c(unsigned int size);
extern void *func_ov004_022110e4(void *);
extern char data_ov004_022524a0;
extern char data_ov004_0225254c;
extern void *func_ov004_02210cf0(void *);
extern void func_ov004_02211518(void *self);

void *func_ov004_02214434(void *this);

void func_ov004_02214458(void)
{
    void *conditionInput0;

    if ((conditionInput0 = (void *) (func_ov004_0221152c(0x848)))) {
        func_ov004_02214434((void *) conditionInput0);
    }
}

void *func_ov004_02214434(void *this)
{
    func_ov004_022110e4(this);
    *(void **) this = &data_ov004_022524a0;
    *(void **) ((char *) this + 0xec) = &data_ov004_0225254c;
    return this;
}

void *func_ov004_02214410(UnkStruct_02214410 *obj)
{
    obj->unk_00 = ((int *) &data_ov004_022524a0);
    obj->unk_EC = ((int *) &data_ov004_0225254c);
    func_ov004_02210cf0(obj);
    return obj;
}

UnkStruct_022143e4 *func_ov004_022143e4(UnkStruct_022143e4 *self)
{
    self->unk_00 = (unsigned int) ((unsigned int *) &data_ov004_022524a0);
    self->unk_EC = (unsigned int) ((unsigned int *) &data_ov004_0225254c);
    func_ov004_02210cf0(self);
    func_ov004_02211518(self);
    return self;
}
