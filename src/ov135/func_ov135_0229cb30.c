/* func_ov135_0229cb30 @ 0x0229cb30, 0x24 bytes, Thumb, module ov135
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *p);
extern void func_ov135_0229c66c(void *p);
extern void func_ov002_02208098(void *p, unsigned char c);

struct UnkStruct_0229cb30 {
    char pad_00[0x94];
    unsigned char unk_94;
    char pad_95[3];
    void *unk_98;
};

void func_ov135_0229cb30(struct UnkStruct_0229cb30 *self)
{
    if (func_0208e484(&self->unk_98) != 0) {
        func_ov135_0229c66c(self);
        func_ov002_02208098(self, self->unk_94);
    }
}
