/* func_ov070_022798b0 @ 0x022798b0, 0x24 bytes, Thumb, module ov070
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201612c(void *p);

struct Pair {
    unsigned int unk_00;
    unsigned int w1;
};

extern struct Pair __ptmf_null;

struct UnkStruct_022798b0 {
    char pad_00[0xb8];
    struct Pair sub;
};

void func_ov070_022798b0(struct UnkStruct_022798b0 *self)
{
    func_0201612c(self);
    self->sub = __ptmf_null;
}
