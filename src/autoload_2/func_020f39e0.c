/* func_020f39e0 @ 0x020f39e0, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

struct Func020f39e0 {
    void *unk_00;
    unsigned char unk_04;
};

extern void func_020f45c4(struct Func020f39e0 *self);
extern char data_0213ea38;

struct Func020f39e0 *func_020f39e0(struct Func020f39e0 *self)
{
    func_020f45c4(self);
    self->unk_00 = &data_0213ea38;
    self->unk_04 = 0x13;
    return self;
}
