/* room_object_02252824_5: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02214c34 @ 0x02214c34, 0x1c bytes, Thumb
 * func_ov004_02214c10 @ 0x02214c10, 0x24 bytes, Thumb
 * func_ov004_02214bec @ 0x02214bec, 0x24 bytes, Thumb
 * func_ov004_02214bc0 @ 0x02214bc0, 0x2c bytes, Thumb
 */

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_02214bec;

typedef struct {
    unsigned int unk_00;
    unsigned char pad_04[0xe8];
    unsigned int unk_EC;
} UnkStruct_02214bc0;

extern int func_ov004_0221152c(unsigned int size);
extern void *func_ov004_022110e4(void *);
extern char data_ov004_02252824;
extern char data_ov004_022528d0;
extern void *func_ov004_02210cf0(void *);
extern void func_ov004_02211518(void *self);

void *func_ov004_02214c10(void *this);

void func_ov004_02214c34(void)
{
    void *conditionInput0;

    if ((conditionInput0 = (void *) (func_ov004_0221152c(0x848)))) {
        func_ov004_02214c10((void *) conditionInput0);
    }
}

void *func_ov004_02214c10(void *this)
{
    func_ov004_022110e4(this);
    *(void **) this = &data_ov004_02252824;
    *(void **) ((char *) this + 0xec) = &data_ov004_022528d0;
    return this;
}

void *func_ov004_02214bec(UnkStruct_02214bec *obj)
{
    obj->unk_00 = ((int *) &data_ov004_02252824);
    obj->unk_EC = ((int *) &data_ov004_022528d0);
    func_ov004_02210cf0(obj);
    return obj;
}

UnkStruct_02214bc0 *func_ov004_02214bc0(UnkStruct_02214bc0 *self)
{
    self->unk_00 = (unsigned int) ((unsigned int *) &data_ov004_02252824);
    self->unk_EC = (unsigned int) ((unsigned int *) &data_ov004_022528d0);
    func_ov004_02210cf0(self);
    func_ov004_02211518(self);
    return self;
}
