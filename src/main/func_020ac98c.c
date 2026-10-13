/* func_020ac98c @ 0x020ac98c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ac8a8(void *arg);
extern unsigned char data_020e3fb4;

struct Struct020ac98c {
    unsigned char *unk_00;
};

void *func_020ac98c(struct Struct020ac98c *self)
{
    self->unk_00 = &data_020e3fb4;
    func_020ac8a8(self);
    return self;
}
