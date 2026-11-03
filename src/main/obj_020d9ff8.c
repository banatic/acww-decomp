/* obj_020d9ff8: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0202eb70 @ 0x0202eb70, 0x18 bytes, Thumb
 * func_0202eb58 @ 0x0202eb58, 0x18 bytes, Thumb
 * func_0202eb38 @ 0x0202eb38, 0x20 bytes, Thumb
 * func_0202eb20 @ 0x0202eb20, 0x18 bytes, Thumb
 */

typedef struct UnkStruct_0202eb38 {
    void *unk_00;
} UnkStruct_0202eb38;

struct UnkStruct_0202eb20 {
    void *p;
};

extern void *func_020161ac(void *arg);
extern void *func_0201615c(void *self);
extern void func_020edb3c(UnkStruct_0202eb38 *);
extern unsigned char data_020d9ff8[];

void *func_0202eb70(void *arg)
{
    func_020161ac(arg);
    *(void **) arg = ((int *) data_020d9ff8);
    return arg;
}

void *func_0202eb58(void *self)
{
    *(void **) self = ((int *) data_020d9ff8);
    func_0201615c(self);
    return self;
}

UnkStruct_0202eb38 *func_0202eb38(UnkStruct_0202eb38 *self)
{
    self->unk_00 = (void *) data_020d9ff8;
    func_0201615c((void *) self);
    func_020edb3c(self);
    return self;
}

void *func_0202eb20(struct UnkStruct_0202eb20 *self)
{
    self->p = ((int *) data_020d9ff8);
    func_0201615c(self);
    return self;
}
