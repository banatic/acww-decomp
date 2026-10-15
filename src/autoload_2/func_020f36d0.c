/* func_020f36d0 @ 0x020f36d0, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020f45c4(void *self);
extern unsigned char data_0213eb08[];

struct func_020f36d0_s {
    void *vtbl;
    unsigned char unk_04;
};

void *func_020f36d0(struct func_020f36d0_s *self)
{
    func_020f45c4(self);
    self->vtbl = data_0213eb08;
    self->unk_04 = 0x17;
    return self;
}
