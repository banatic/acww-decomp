/* func_ov111_0229f1fc @ 0x0229f1fc, 0x50 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov111_0229efb8(void *p, int n);
extern void func_ov095_02299aec(void *p);
extern int func_ov095_02299b7c(void *p);
extern int func_ov095_02299b38(void *p);
extern void func_ov002_0220a0b4(void *p, int a, int b);
extern void func_ov002_0220a374(void *p, int n);
extern void func_ov111_0229f0a4(void *p);

typedef struct Struct_ov111_0229f1fc {
    char pad_00[0xac];
    int unk_AC;
    char pad_B0[0x3d38 - 0xac - 4];
    int unk_3D38;
} Struct_ov111_0229f1fc;

void func_ov111_0229f1fc(Struct_ov111_0229f1fc *self)
{
    int a;
    int b;

    func_ov111_0229efb8(self, 2);
    func_ov095_02299aec(&self->unk_AC);
    a = func_ov095_02299b7c(&self->unk_AC);
    b = func_ov095_02299b38(&self->unk_AC);
    func_ov002_0220a0b4(&self->unk_3D38, a, b);
    func_ov002_0220a374(&self->unk_3D38, 1);
    func_ov111_0229f0a4(self);
}
