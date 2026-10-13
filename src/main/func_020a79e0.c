/* func_020a79e0 @ 0x020a79e0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Object {
    int *vtable;
};

extern int data_020e3d14;
extern void func_020edb3c(struct Object *self);

struct Object *func_020a79e0(struct Object *self)
{
    self->vtable = &data_020e3d14;
    func_020edb3c(self);
    return self;
}
