/* room_object_02252cd4_2: 5 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02218b10 @ 0x02218b10, 0x1c bytes, Thumb
 * func_ov004_02218aec @ 0x02218aec, 0x24 bytes, Thumb
 * func_ov004_02218ac8 @ 0x02218ac8, 0x24 bytes, Thumb
 * func_ov004_02218a9c @ 0x02218a9c, 0x2c bytes, Thumb
 * func_ov004_02218a5c @ 0x02218a5c, 0x40 bytes, Thumb
 */

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_02218ac8;

typedef struct {
    unsigned int unk_00;
    unsigned char pad_04[0xe8];
    unsigned int unk_EC;
} UnkStruct_02218a9c;

extern int func_ov004_0221152c(unsigned int size);
extern void *func_ov004_022110e4(void *);
extern char data_ov004_02252cd4;
extern char data_ov004_02252d80;
extern void *func_ov004_02210cf0(void *);
extern void func_ov004_02211518(void *self);
extern void func_ov004_0220cfec(void *, int);
extern void func_ov004_0221041c(void *, int, int, int, int);

void *func_ov004_02218aec(void *this);

void func_ov004_02218b10(void)
{
    void *conditionInput0;

    if ((conditionInput0 = (void *) (func_ov004_0221152c(0x848)))) {
        func_ov004_02218aec((void *) conditionInput0);
    }
}

void *func_ov004_02218aec(void *this)
{
    func_ov004_022110e4(this);
    *(void **) this = &data_ov004_02252cd4;
    *(void **) ((char *) this + 0xec) = &data_ov004_02252d80;
    return this;
}

void *func_ov004_02218ac8(UnkStruct_02218ac8 *obj)
{
    obj->unk_00 = ((int *) &data_ov004_02252cd4);
    obj->unk_EC = ((int *) &data_ov004_02252d80);
    func_ov004_02210cf0(obj);
    return obj;
}

UnkStruct_02218a9c *func_ov004_02218a9c(UnkStruct_02218a9c *self)
{
    self->unk_00 = (unsigned int) ((unsigned int *) &data_ov004_02252cd4);
    self->unk_EC = (unsigned int) ((unsigned int *) &data_ov004_02252d80);
    func_ov004_02210cf0(self);
    func_ov004_02211518(self);
    return self;
}

int func_ov004_02218a5c(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0220cfec(self + 0x764, 0x0);
    if (*(int *) (self + 0x780) == 0x9 || *(int *) (self + 0x780) == 0x2c) {
        func_ov004_0221041c(self, 0x0, 0x0, 0x1000, 0x0);
    }
    return 0x1;
}
