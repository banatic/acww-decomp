/* overlay_task: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206f4bc @ 0x0206f4bc, 0x28 bytes, Thumb
 * func_0206f49c @ 0x0206f49c, 0x20 bytes, Thumb
 */

struct UnkStruct_0206f4bc {
    void *volatile unk_00;
};

extern void func_020ee62c(void *self);
extern void func_020edf54(void *self);
extern unsigned char data_020da13c[];
extern unsigned char data_020df548[];

struct UnkStruct_0206f4bc *func_0206f4bc(struct UnkStruct_0206f4bc *self)
{
    self->unk_00 = ((char *) data_020df548);
    self->unk_00 = ((char *) data_020da13c);
    func_020ee62c(self);
    func_020edf54(self);
    return self;
}

void *func_0206f49c(void *ptr)
{
    volatile void **p = (volatile void **) ptr;
    *p = (void *) data_020df548;
    *p = (void *) data_020da13c;
    func_020ee62c(ptr);
    return ptr;
}
