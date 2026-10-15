/* func_020f3808 @ 0x020f3808, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020f3808 {
    void *vtable;
};

extern char data_0213eaa0;
extern void *func_020f4514(struct UnkStruct_020f3808 *self);
extern void func_020edb3c(struct UnkStruct_020f3808 *self);

void *func_020f3808(struct UnkStruct_020f3808 *self)
{
    self->vtable = &data_0213eaa0;
    func_020f4514(self);
    func_020edb3c(self);
    return self;
}
