/* func_ov144_0229a264 @ 0x0229a264, 0x36 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229a264 UnkStruct_0229a264;
struct UnkStruct_0229a264 {
    unsigned char pad_00[0xc4];
    int unk_C4;
};

extern int func_ov144_0229a208(UnkStruct_0229a264 *self);
extern int func_ov144_0229a198(UnkStruct_0229a264 *self);
extern void func_ov144_0229a0e0(UnkStruct_0229a264 *self);
extern void func_ov002_0220a0b4(void *ptr, int a, int b);
extern void func_ov002_0220a374(void *ptr, int a);

void func_ov144_0229a264(UnkStruct_0229a264 *self)
{
    int a;
    int b;

    a = func_ov144_0229a208(self);
    b = func_ov144_0229a198(self);
    func_ov002_0220a0b4(&self->unk_C4, a, b);
    func_ov002_0220a374(&self->unk_C4, 1);
    func_ov144_0229a0e0(self);
}
