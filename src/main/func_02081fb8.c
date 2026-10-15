/* func_02081fb8 @ 0x02081fb8, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02081fb8 {
    void *vtable;
};

extern char data_020e18ec;
extern void *func_020a887c(struct UnkStruct_02081fb8 *);
extern void func_020edb3c(struct UnkStruct_02081fb8 *);

struct UnkStruct_02081fb8 *func_02081fb8(struct UnkStruct_02081fb8 *self)
{
    self->vtable = &data_020e18ec;
    func_020a887c(self);
    func_020edb3c(self);
    return self;
}
