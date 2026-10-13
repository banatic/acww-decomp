/* func_ov115_0229e074 @ 0x0229e074, 0x4c bytes, Thumb, module ov115
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov114_0229d2d8(void *p);
extern void func_ov002_02208098(void *p, int n);
extern void func_ov114_0229d52c(void *p, int v);
extern int func_ov115_0229dedc(void *p);
extern int func_ov115_0229ded0(void *p);
extern void func_ov002_0220a0b4(void *p, int a, int b);

typedef struct {
    unsigned char pad_00[0x94];
    unsigned char unk_94;
    unsigned char pad_95[0x63];
    int unk_F8;
    unsigned char pad_FC[0x1328];
    int unk_1424;
} UnkStruct_0229e074;

void func_ov115_0229e074(UnkStruct_0229e074 *self)
{
    int a, b;

    if (func_ov114_0229d2d8(&self->unk_F8) != 0) {
        func_ov002_02208098(self, 7);
    }
    func_ov114_0229d52c(&self->unk_F8, self->unk_1424);
    a = func_ov115_0229dedc(self);
    b = func_ov115_0229ded0(self);
    func_ov002_0220a0b4(&self->unk_94, a, b);
}
