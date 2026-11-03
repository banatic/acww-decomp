/* room_object_0225130c_5: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02212fec @ 0x02212fec, 0x1c bytes, Thumb
 * func_ov004_02212fc8 @ 0x02212fc8, 0x24 bytes, Thumb
 * func_ov004_02212fa4 @ 0x02212fa4, 0x24 bytes, Thumb
 * func_ov004_02212f78 @ 0x02212f78, 0x2c bytes, Thumb
 */

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_02212fa4;

typedef struct {
    unsigned int unk_00;
    unsigned char pad_04[0xe8];
    unsigned int unk_EC;
} UnkStruct_02212f78;

extern int func_ov004_0221152c(unsigned int size);
extern void *func_ov004_022110e4(void *);
extern char data_ov004_0225130c;
extern char data_ov004_022513b8;
extern void *func_ov004_02210cf0(void *);
extern void func_ov004_02211518(void *self);

void *func_ov004_02212fc8(void *this);

void func_ov004_02212fec(void)
{
    void *conditionInput0;

    if ((conditionInput0 = (void *) (func_ov004_0221152c(0x848)))) {
        func_ov004_02212fc8((void *) conditionInput0);
    }
}

void *func_ov004_02212fc8(void *this)
{
    func_ov004_022110e4(this);
    *(void **) this = &data_ov004_0225130c;
    *(void **) ((char *) this + 0xec) = &data_ov004_022513b8;
    return this;
}

void *func_ov004_02212fa4(UnkStruct_02212fa4 *obj)
{
    obj->unk_00 = ((int *) &data_ov004_0225130c);
    obj->unk_EC = ((int *) &data_ov004_022513b8);
    func_ov004_02210cf0(obj);
    return obj;
}

UnkStruct_02212f78 *func_ov004_02212f78(UnkStruct_02212f78 *self)
{
    self->unk_00 = (unsigned int) ((unsigned int *) &data_ov004_0225130c);
    self->unk_EC = (unsigned int) ((unsigned int *) &data_ov004_022513b8);
    func_ov004_02210cf0(self);
    func_ov004_02211518(self);
    return self;
}
