/* func_ov135_0229d498 @ 0x0229d498, 0x1e bytes, Thumb, module ov135
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov135_0229d0e8(void *self);
extern unsigned char *func_ov002_022080a0(void *, unsigned char);

typedef struct UnkStruct_0229d498 {
    unsigned char pad_00[0x8c];
    unsigned char unk_8C;
} UnkStruct_0229d498;

int func_ov135_0229d498(UnkStruct_0229d498 *self)
{
    func_ov135_0229d0e8(self);
    self->unk_8C = 0;
    func_ov002_022080a0(self, 0);
    return 1;
}
