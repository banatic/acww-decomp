/* func_020b400c @ 0x020b400c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8188(void *);
extern void func_020edb3c(void *);
extern char data_020e5200;

struct UnkStruct_020b400c {
    void *vtable;
};

void *func_020b400c(struct UnkStruct_020b400c *self)
{
    self->vtable = &data_020e5200;
    func_020a8188(self);
    func_020edb3c(self);
    return self;
}
