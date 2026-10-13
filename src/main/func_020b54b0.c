/* func_020b54b0 @ 0x020b54b0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *vtable;
} Object;
extern char data_020e51e8;
extern void func_020a9a40(Object *self);

Object *func_020b54b0(Object *self)
{
    self->vtable = &data_020e51e8;
    func_020a9a40(self);
    return self;
}
