/* room_object_022510b4_3: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02218f0c @ 0x02218f0c, 0x1c bytes, Thumb
 * func_ov004_02218ee8 @ 0x02218ee8, 0x24 bytes, Thumb
 * func_ov004_02218ec4 @ 0x02218ec4, 0x24 bytes, Thumb
 * func_ov004_02218e98 @ 0x02218e98, 0x2c bytes, Thumb
 */

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_02218ec4;

typedef struct {
    unsigned int unk_00;
    unsigned char pad_04[0xe8];
    unsigned int unk_EC;
} UnkStruct_02218e98;

extern int func_ov004_0221152c(unsigned int size);
extern void *func_ov004_022110e4(void *);
extern char data_ov004_022510b4;
extern char data_ov004_02251160;
extern void *func_ov004_02210cf0(void *);
extern void func_ov004_02211518(void *self);

void *func_ov004_02218ee8(void *this);

void func_ov004_02218f0c(void)
{
    void *conditionInput0;

    if ((conditionInput0 = (void *) (func_ov004_0221152c(0x848)))) {
        func_ov004_02218ee8((void *) conditionInput0);
    }
}

void *func_ov004_02218ee8(void *this)
{
    func_ov004_022110e4(this);
    *(void **) this = &data_ov004_022510b4;
    *(void **) ((char *) this + 0xec) = &data_ov004_02251160;
    return this;
}

void *func_ov004_02218ec4(UnkStruct_02218ec4 *obj)
{
    obj->unk_00 = ((int *) &data_ov004_022510b4);
    obj->unk_EC = ((int *) &data_ov004_02251160);
    func_ov004_02210cf0(obj);
    return obj;
}

UnkStruct_02218e98 *func_ov004_02218e98(UnkStruct_02218e98 *self)
{
    self->unk_00 = (unsigned int) ((unsigned int *) &data_ov004_022510b4);
    self->unk_EC = (unsigned int) ((unsigned int *) &data_ov004_02251160);
    func_ov004_02210cf0(self);
    func_ov004_02211518(self);
    return self;
}
