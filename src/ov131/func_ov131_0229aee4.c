/* func_ov131_0229aee4 @ 0x0229aee4, 0x28 bytes, Thumb, module ov131
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229aee4 {
    unsigned char pad_00[0x8D];
    unsigned char unk_8D;
    unsigned char pad_8E[0x14C8];
    unsigned char unk_1556;
};

extern void func_ov002_0220a164(void *p);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov131_0229aee4(struct UnkStruct_0229aee4 *self)
{
    func_ov002_0220a164((char *) self + 0x94);
    self->unk_1556 = self->unk_8D;
    func_ov002_02208098((void *) (self), 5);
}
