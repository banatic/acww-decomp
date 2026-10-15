/* func_020f27c4 @ 0x020f27c4, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020f27c4 {
    void *unk_00;
};

extern void *func_020f4514(struct UnkStruct_020f27c4 *self);
extern void func_020edb3c(struct UnkStruct_020f27c4 *self);
extern char data_0213eeb0;

void *func_020f27c4(struct UnkStruct_020f27c4 *self)
{
    self->unk_00 = &data_0213eeb0;
    func_020f4514(self);
    func_020edb3c(self);
    return self;
}
