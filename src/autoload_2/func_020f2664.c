/* func_020f2664 @ 0x020f2664, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020f3fe0(void *);
extern int data_0213ef18;

struct UnkStruct_020f2664 {
    void *unk_00;
    unsigned char unk_04;
};

void *func_020f2664(struct UnkStruct_020f2664 *self)
{
    func_020f3fe0(self);
    self->unk_00 = &data_0213ef18;
    self->unk_04 = 0x3c;
    return self;
}
