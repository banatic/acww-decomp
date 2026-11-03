/* view_process: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b9464 @ 0x020b9464, 0x12 bytes, Thumb
 * func_020b943c @ 0x020b943c, 0x28 bytes, Thumb
 * func_020b941c @ 0x020b941c, 0x20 bytes, Thumb
 */

struct UnkStruct_020b943c {
    union {
        void *ptr_a;
        void *ptr_b;
    } u;
};

extern void func_02002e98(void *ptr);
extern void func_020ee62c(void *);
extern void func_020edf54(void *);
extern unsigned char data_020da13c[];
extern unsigned char data_020e58cc[];

int func_020b9464(void *arg)
{
    func_02002e98((void *) ((char *) arg + 0x50));
    return 1;
}

void *func_020b943c(struct UnkStruct_020b943c *self)
{
    self->u.ptr_a = (void *) data_020e58cc;
    self->u.ptr_b = (void *) data_020da13c;
    func_020ee62c(self);
    func_020edf54(self);
    return self;
}

void *func_020b941c(void *self)
{
    volatile int *p = (volatile int *) self;
    *p = (unsigned int) data_020e58cc;
    *p = (unsigned int) data_020da13c;
    func_020ee62c(self);
    return self;
}
