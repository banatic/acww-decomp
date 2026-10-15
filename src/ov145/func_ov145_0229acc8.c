/* func_ov145_0229acc8 @ 0x0229acc8, 0x1e bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_ov145 {
    unsigned char unk_00[0x8c];
    unsigned char unk_8C;
};

extern void func_ov145_0229a884(struct UnkStruct_ov145 *self);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);

int func_ov145_0229acc8(struct UnkStruct_ov145 *self)
{
    func_ov145_0229a884(self);
    self->unk_8C = 0;
    func_ov002_022080a0((void *) (self), 0);
    return 1;
}
