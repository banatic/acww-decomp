/* func_0208fe5c @ 0x0208fe5c, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e246c;
extern void func_0208a1f4(void *);
extern void func_0208af00(void *);

struct UnkStruct_0208fe5c {
    void *unk_00;
    char pad_04[0x10];
    char sub;
};

struct UnkStruct_0208fe5c *func_0208fe5c(struct UnkStruct_0208fe5c *self)
{
    self->unk_00 = &data_020e246c;
    func_0208a1f4(&self->sub);
    func_0208af00(self);
    return self;
}
