/* bromide_3: 5 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022136dc @ 0x022136dc, 0x1c bytes, Thumb
 * func_ov004_022136b8 @ 0x022136b8, 0x24 bytes, Thumb
 * func_ov004_02213694 @ 0x02213694, 0x24 bytes, Thumb
 * func_ov004_02213668 @ 0x02213668, 0x2c bytes, Thumb
 * func_ov004_02213664 @ 0x02213664, 0x4 bytes, Thumb
 */

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_02213694;

typedef struct {
    unsigned int unk_00;
    unsigned char pad_04[0xe8];
    unsigned int unk_EC;
} UnkStruct_02213668;

extern int func_ov004_0221152c(unsigned int size);
extern void *func_ov004_022110e4(void *);
extern char data_ov004_02251b40;
extern char data_ov004_02251bec;
extern void *func_ov004_02210cf0(void *);
extern void func_ov004_02211518(void *self);

void *func_ov004_022136b8(void *this);

void func_ov004_022136dc(void)
{
    void *conditionInput0;

    if ((conditionInput0 = (void *) (func_ov004_0221152c(0x848)))) {
        func_ov004_022136b8((void *) conditionInput0);
    }
}

void *func_ov004_022136b8(void *this)
{
    func_ov004_022110e4(this);
    *(void **) this = &data_ov004_02251b40;
    *(void **) ((char *) this + 0xec) = &data_ov004_02251bec;
    return this;
}

void *func_ov004_02213694(UnkStruct_02213694 *obj)
{
    obj->unk_00 = ((int *) &data_ov004_02251b40);
    obj->unk_EC = ((int *) &data_ov004_02251bec);
    func_ov004_02210cf0(obj);
    return obj;
}

UnkStruct_02213668 *func_ov004_02213668(UnkStruct_02213668 *self)
{
    self->unk_00 = (unsigned int) ((unsigned int *) &data_ov004_02251b40);
    self->unk_EC = (unsigned int) ((unsigned int *) &data_ov004_02251bec);
    func_ov004_02210cf0(self);
    func_ov004_02211518(self);
    return self;
}

int func_ov004_02213664(void)
{
    return 1;
}
