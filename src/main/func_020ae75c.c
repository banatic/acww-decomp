/* func_020ae75c @ 0x020ae75c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8c38(void *);
extern int data_020e4170;

struct UnkStruct_020ae75c {
    void *unk_00;
};

struct UnkStruct_020ae75c *func_020ae75c(struct UnkStruct_020ae75c *self)
{
    self->unk_00 = (void *) &data_020e4170;
    func_020a8c38(self);
    return self;
}
