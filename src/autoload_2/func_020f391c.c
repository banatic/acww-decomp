/* func_020f391c @ 0x020f391c, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f45c4(void *p);
extern unsigned char data_0213ea6c[];

struct UnkStruct_020f391c {
    void *unk_00;
    unsigned char unk_04;
};

struct UnkStruct_020f391c *func_020f391c(struct UnkStruct_020f391c *self)
{
    func_020f45c4(self);
    self->unk_00 = data_0213ea6c;
    self->unk_04 = 0x14;
    return self;
}
