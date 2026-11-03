/* room_object_02250d30: 7 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02212748 @ 0x02212748, 0x1c bytes, Thumb
 * func_ov004_02212724 @ 0x02212724, 0x24 bytes, Thumb
 * func_ov004_02212700 @ 0x02212700, 0x24 bytes, Thumb
 * func_ov004_022126d4 @ 0x022126d4, 0x2c bytes, Thumb
 * func_ov004_022126b8 @ 0x022126b8, 0x1c bytes, Thumb
 * func_ov004_022126b4 @ 0x022126b4, 0x4 bytes, Thumb
 * func_ov004_022126b0 @ 0x022126b0, 0x4 bytes, Thumb
 */

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_02212700;

typedef struct {
    unsigned int unk_00;
    unsigned char pad_04[0xe8];
    unsigned int unk_EC;
} UnkStruct_022126d4;

extern int func_ov004_0221152c(unsigned int size);
extern void *func_ov004_022110e4(void *);
extern char data_ov004_02250d30;
extern char data_ov004_02250ddc;
extern void *func_ov004_02210cf0(void *);
extern void func_ov004_02211518(void *self);
extern int func_ov004_0223d03c(void);
extern short func_ov004_0223d2ac(int v);

void *func_ov004_02212724(void *this);

void func_ov004_02212748(void)
{
    void *conditionInput0;

    if ((conditionInput0 = (void *) (func_ov004_0221152c(0x848)))) {
        func_ov004_02212724((void *) conditionInput0);
    }
}

void *func_ov004_02212724(void *this)
{
    func_ov004_022110e4(this);
    *(void **) this = &data_ov004_02250d30;
    *(void **) ((char *) this + 0xec) = &data_ov004_02250ddc;
    return this;
}

void *func_ov004_02212700(UnkStruct_02212700 *obj)
{
    obj->unk_00 = ((int *) &data_ov004_02250d30);
    obj->unk_EC = ((int *) &data_ov004_02250ddc);
    func_ov004_02210cf0(obj);
    return obj;
}

UnkStruct_022126d4 *func_ov004_022126d4(UnkStruct_022126d4 *self)
{
    self->unk_00 = (unsigned int) ((unsigned int *) &data_ov004_02250d30);
    self->unk_EC = (unsigned int) ((unsigned int *) &data_ov004_02250ddc);
    func_ov004_02210cf0(self);
    func_ov004_02211518(self);
    return self;
}

int func_ov004_022126b8(char *self)
{
    *(short *) (self + 0x844) = func_ov004_0223d2ac(func_ov004_0223d03c());
    return 1;
}

int func_ov004_022126b4(void)
{
    return 1;
}

int func_ov004_022126b0(void)
{
    return 1;
}
