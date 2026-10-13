/* func_02083cc0 @ 0x02083cc0, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e1cc0;
extern char data_020da13c;

struct UnkStruct_02083cc0 {
    void *vtable;
    char pad_04[0x4c];
    char sub;
};

extern void func_02084f84(char *ptr);
extern void func_020ee62c(void *ptr);

struct UnkStruct_02083cc0 *func_02083cc0(struct UnkStruct_02083cc0 *self)
{
    self->vtable = &data_020e1cc0;
    func_02084f84(&self->sub);
    self->vtable = &data_020da13c;
    func_020ee62c(self);
    return self;
}
