/* room_object_02251564_2: 5 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02213254 @ 0x02213254, 0x1c bytes, Thumb
 * func_ov004_02213230 @ 0x02213230, 0x24 bytes, Thumb
 * func_ov004_0221320c @ 0x0221320c, 0x24 bytes, Thumb
 * func_ov004_022131e0 @ 0x022131e0, 0x2c bytes, Thumb
 * func_ov004_022131c8 @ 0x022131c8, 0x16 bytes, Thumb
 */

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_0221320c;

typedef struct {
    unsigned int unk_00;
    unsigned char pad_04[0xe8];
    unsigned int unk_EC;
} UnkStruct_022131e0;

typedef struct UnkStruct_022131c8 UnkStruct_022131c8;

struct UnkStruct_022131c8 {
    void (**vt)(UnkStruct_022131c8 *, int, int);
};

extern int func_ov004_0221152c(unsigned int size);
extern void *func_ov004_022110e4(void *);
extern char data_ov004_02251564;
extern char data_ov004_02251610;
extern void *func_ov004_02210cf0(void *);
extern void func_ov004_02211518(void *self);

void *func_ov004_02213230(void *this);

void func_ov004_02213254(void)
{
    void *conditionInput0;

    if ((conditionInput0 = (void *) (func_ov004_0221152c(0x848)))) {
        func_ov004_02213230((void *) conditionInput0);
    }
}

void *func_ov004_02213230(void *this)
{
    func_ov004_022110e4(this);
    *(void **) this = &data_ov004_02251564;
    *(void **) ((char *) this + 0xec) = &data_ov004_02251610;
    return this;
}

void *func_ov004_0221320c(UnkStruct_0221320c *obj)
{
    obj->unk_00 = ((int *) &data_ov004_02251564);
    obj->unk_EC = ((int *) &data_ov004_02251610);
    func_ov004_02210cf0(obj);
    return obj;
}

UnkStruct_022131e0 *func_ov004_022131e0(UnkStruct_022131e0 *self)
{
    self->unk_00 = (unsigned int) ((unsigned int *) &data_ov004_02251564);
    self->unk_EC = (unsigned int) ((unsigned int *) &data_ov004_02251610);
    func_ov004_02210cf0(self);
    func_ov004_02211518(self);
    return self;
}

int func_ov004_022131c8(UnkStruct_022131c8 *self)
{
    self->vt[28](self, 0, 0xff);
    return 1;
}
