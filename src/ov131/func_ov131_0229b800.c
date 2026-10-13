/* func_ov131_0229b800 @ 0x0229b800, 0x1e bytes, Thumb, module ov131
 * mwccarm 1.2/base -O4,s
 */

typedef struct SelfType {
    unsigned char pad_00[0x8c];
    unsigned char flag;
} SelfType;

extern void func_ov131_0229b4cc(SelfType *self);
extern void func_ov002_022080a0(SelfType *self);

int func_ov131_0229b800(SelfType *self)
{
    func_ov131_0229b4cc(self);
    self->flag = 0;
    func_ov002_022080a0(self);
    return 1;
}
