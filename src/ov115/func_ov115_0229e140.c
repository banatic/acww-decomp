/* func_ov115_0229e140 @ 0x0229e140, 0x28 bytes, Thumb, module ov115
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f64(void *p);
extern void func_ov002_02208098(void *self, unsigned char b);
extern void func_ov115_0229e5e8(void *self);

struct UnkStruct_0229e140 {
    char pad_00[0x94];
    char unk_94;
    char pad_95[0x142C - 0x94 - 1];
    unsigned char unk_142C;
};

void func_ov115_0229e140(struct UnkStruct_0229e140 *self)
{
    if (func_ov002_02209f64(&self->unk_94) == 0) {
        func_ov002_02208098(self, self->unk_142C);
        func_ov115_0229e5e8(self);
    }
}
