/* func_02066a64 @ 0x02066a64, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020def4c;
extern void func_020a8c38(void *);
extern void func_020edb3c(void *);

struct UnkStruct_02066a64 {
    void *vtbl;
};

struct UnkStruct_02066a64 *func_02066a64(struct UnkStruct_02066a64 *self)
{
    self->vtbl = &data_020def4c;
    func_020a8c38(self);
    func_020edb3c(self);
    return self;
}
