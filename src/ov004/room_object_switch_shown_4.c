/* room_object_switch_shown_4: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02212694 @ 0x02212694, 0x1c bytes, Thumb
 * func_ov004_02212670 @ 0x02212670, 0x24 bytes, Thumb
 * func_ov004_0221264c @ 0x0221264c, 0x24 bytes, Thumb
 * func_ov004_02212620 @ 0x02212620, 0x2c bytes, Thumb
 */

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_0221264c;

typedef struct {
    unsigned int unk_00;
    unsigned char pad_04[0xe8];
    unsigned int unk_EC;
} UnkStruct_02212620;

extern int func_ov004_0221152c(unsigned int size);
extern void *func_ov004_022110e4(void *);
extern char data_ov004_02250ad8;
extern char data_ov004_02250b84;
extern void *func_ov004_02210cf0(void *);
extern void func_ov004_02211518(void *self);

void *func_ov004_02212670(void *this);

void func_ov004_02212694(void)
{
    void *conditionInput0;

    if ((conditionInput0 = (void *) (func_ov004_0221152c(0x848)))) {
        func_ov004_02212670((void *) conditionInput0);
    }
}

void *func_ov004_02212670(void *this)
{
    func_ov004_022110e4(this);
    *(void **) this = &data_ov004_02250ad8;
    *(void **) ((char *) this + 0xec) = &data_ov004_02250b84;
    return this;
}

void *func_ov004_0221264c(UnkStruct_0221264c *obj)
{
    obj->unk_00 = ((int *) &data_ov004_02250ad8);
    obj->unk_EC = ((int *) &data_ov004_02250b84);
    func_ov004_02210cf0(obj);
    return obj;
}

UnkStruct_02212620 *func_ov004_02212620(UnkStruct_02212620 *self)
{
    self->unk_00 = (unsigned int) ((unsigned int *) &data_ov004_02250ad8);
    self->unk_EC = (unsigned int) ((unsigned int *) &data_ov004_02250b84);
    func_ov004_02210cf0(self);
    func_ov004_02211518(self);
    return self;
}
