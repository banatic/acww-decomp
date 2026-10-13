/* func_020f2cb4 @ 0x020f2cb4, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f45c4(void *);
extern int data_0213ed78;

struct UnkStruct_020f2cb4 {
    void *unk_00;
    unsigned char unk_04;
};

struct UnkStruct_020f2cb4 *func_020f2cb4(struct UnkStruct_020f2cb4 *self)
{
    func_020f45c4(self);
    self->unk_00 = &data_0213ed78;
    self->unk_04 = 0x2c;
    return self;
}
