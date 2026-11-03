/* barber_talk_2: 3 functions, module ov053
 * mwccarm 1.2/base -O4,s
 * func_ov053_02260c14 @ 0x02260c14, 0x18 bytes, Thumb
 * func_ov053_02260bfc @ 0x02260bfc, 0x18 bytes, Thumb
 * func_ov053_02260bdc @ 0x02260bdc, 0x20 bytes, Thumb
 */

struct UnkStruct_02260bdc {
    void *vtable;
};

extern void *func_0202eb70(void *);
extern void *func_0202eb20(void *);
extern void func_020edb3c(void *p);
extern unsigned char data_ov053_02261b08[];

void *func_ov053_02260c14(void *this)
{
    func_0202eb70(this);
    *(unsigned int *) this = (unsigned int) ((unsigned char *) data_ov053_02261b08);
    return this;
}

void *func_ov053_02260bfc(void *p)
{
    *(int *) p = (int) ((int *) data_ov053_02261b08);
    func_0202eb20(p);
    return p;
}

struct UnkStruct_02260bdc *func_ov053_02260bdc(struct UnkStruct_02260bdc *self)
{
    self->vtable = (void *) data_ov053_02261b08;
    func_0202eb20(self);
    func_020edb3c(self);
    return self;
}
