/* func_ov104_0229d3f0 @ 0x0229d3f0, 0x58 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov104_0229d3ac(void *self);
extern int func_ov104_0229d39c(void *self);
extern int func_ov104_0229da5c(void *self, int flag);
extern void func_ov104_0229d198(void *self);
extern void func_ov002_0220a0b4(void *obj, int a, int b);
extern void func_ov002_0220a374(void *obj, int v);

typedef struct UnkStruct_0229d3f0 {
    int pad_00;
} UnkStruct_0229d3f0;

typedef struct UnkStruct_0229d3f0_2 {
    unsigned char pad_00[0xb8];
    unsigned char unk_B8;
    unsigned char pad_B9[0x24a0 - 0xb8 - 1];
    UnkStruct_0229d3f0 obj;
} UnkStruct_0229d3f0_2;

void func_ov104_0229d3f0(UnkStruct_0229d3f0_2 *self)
{
    int a;
    int b;

    a = func_ov104_0229d3ac(self);
    b = func_ov104_0229d39c(self);
    func_ov002_0220a0b4(&self->obj, a, b);

    if (func_ov104_0229da5c(self, self->unk_B8) != 0) {
        func_ov002_0220a374(&self->obj, 7);
    } else {
        func_ov002_0220a374(&self->obj, 1);
    }

    func_ov104_0229d198(self);
}
