/* func_020a8228 @ 0x020a8228, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8cac(void *self);
extern void func_020a81e0(void *self);
extern char data_020e3d64;

struct UnkStruct_020a8228 {
    void *vtable;
};

struct UnkStruct_020a8228 *func_020a8228(struct UnkStruct_020a8228 *self)
{
    func_020a8cac(self);
    self->vtable = &data_020e3d64;
    func_020a81e0(self);
    return self;
}
