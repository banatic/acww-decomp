/* func_020a88a0 @ 0x020a88a0, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e3d7c;
extern char data_020da6c4;
extern void func_020a9b44(void *);
extern void func_020edb3c(void *);

typedef struct {
    void *vtable;
    int sub;
} UnkStruct_020a88a0;

void *func_020a88a0(UnkStruct_020a88a0 *self)
{
    self->vtable = &data_020e3d7c;
    func_020a9b44(&self->sub);
    self->vtable = &data_020da6c4;
    func_020edb3c(self);
    return self;
}
