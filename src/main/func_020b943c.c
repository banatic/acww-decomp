/* func_020b943c @ 0x020b943c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ee62c(void *);
extern void func_020edf54(void *);

struct UnkStruct_020b943c {
    union {
        void *ptr_a;
        void *ptr_b;
    } u;
};

extern unsigned char data_020da13c[];
extern unsigned char data_020e58cc[];

void *func_020b943c(struct UnkStruct_020b943c *self)
{
    self->u.ptr_a = (void *) data_020e58cc;
    self->u.ptr_b = (void *) data_020da13c;
    func_020ee62c(self);
    func_020edf54(self);
    return self;
}
