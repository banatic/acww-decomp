/* func_020b5598 @ 0x020b5598, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e51d0;

struct UnkStruct_020b5598 {
    void *vtable;
};

extern void func_020a8c38(struct UnkStruct_020b5598 *self);
extern void func_020edb3c(struct UnkStruct_020b5598 *self);

struct UnkStruct_020b5598 *func_020b5598(struct UnkStruct_020b5598 *self)
{
    self->vtable = &data_020e51d0;
    func_020a8c38(self);
    func_020edb3c(self);
    return self;
}
