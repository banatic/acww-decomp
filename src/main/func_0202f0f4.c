/* func_0202f0f4 @ 0x0202f0f4, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0202f0f4 {
    void *vtable;
};

extern void func_020ee62c(struct UnkStruct_0202f0f4 *);

extern unsigned char data_020da13c[];

struct UnkStruct_0202f0f4 *func_0202f0f4(struct UnkStruct_0202f0f4 *self)
{
    self->vtable = (void *) data_020da13c;
    func_020ee62c(self);
    return self;
}
