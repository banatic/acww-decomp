/* func_0208e00c @ 0x0208e00c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8c38(void *self);
extern int data_020e21e4;

struct UnkStruct_0208e00c {
    void *vtable;
};

void *func_0208e00c(struct UnkStruct_0208e00c *self)
{
    self->vtable = &data_020e21e4;
    func_020a8c38(self);
    return self;
}
