/* func_020f35fc @ 0x020f35fc, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020f35fc {
    void *unk_00;
    unsigned char unk_04;
};

extern void *func_020f45c4(struct UnkStruct_020f35fc *);
extern char data_0213eb3c;

struct UnkStruct_020f35fc *func_020f35fc(struct UnkStruct_020f35fc *self)
{
    func_020f45c4(self);
    self->unk_00 = &data_0213eb3c;
    self->unk_04 = 0x18;
    return self;
}
