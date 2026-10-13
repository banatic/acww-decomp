/* func_020a8d58 @ 0x020a8d58, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a9260(void *self);
extern void func_020edb3c(void *self);

typedef struct {
    void *vtable;
} UnkStruct_020a8d58;

extern unsigned char data_020e3e04[];

void *func_020a8d58(UnkStruct_020a8d58 *self)
{
    self->vtable = (void *) data_020e3e04;
    func_020a9260(self);
    func_020edb3c(self);
    return self;
}
