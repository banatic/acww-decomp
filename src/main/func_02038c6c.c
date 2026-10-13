/* func_02038c6c @ 0x02038c6c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8cac(void *);
extern void func_020a8c1c(void *);
extern int data_020da548;

struct UnkStruct_02038c6c {
    void *unk_00;
};

struct UnkStruct_02038c6c *func_02038c6c(struct UnkStruct_02038c6c *self)
{
    func_020a8cac(self);
    self->unk_00 = &data_020da548;
    func_020a8c1c(self);
    return self;
}
