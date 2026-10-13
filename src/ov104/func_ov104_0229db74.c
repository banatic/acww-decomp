/* func_ov104_0229db74 @ 0x0229db74, 0x64 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229db74 {
    char data[1];
} UnkStruct_0229db74;
typedef struct UnkStruct_0229db74_2 UnkStruct_0229db74_2;
struct UnkStruct_0229db74_2 {
    char pad_00[0xa8];
    void *unk_A8;
    void *unk_AC;
    char pad_B0[0xb7 - 0xb0];
    unsigned char unk_B7;
    char pad_B8[0x2488 - 0xb8];
    UnkStruct_0229db74 sub;
};

extern void func_ov002_02209d68(void *base, void *a8, void *ac);
extern void func_ov002_02209d38(void *base, int r1, int r2, int r3);
extern void func_ov002_02209d8c(void *base);
extern void func_ov002_02208098(void *self, int value);
extern int func_ov104_0229d8a8(void *self, int value);
extern int func_ov104_0229d858(void *self, int value);
extern void func_ov104_0229d500(void *self);

void func_ov104_0229db74(UnkStruct_0229db74_2 *self, int value, int arg3)
{
    int result1;
    int result2;

    self->unk_B7 = (unsigned char) value;
    func_ov002_02209d68(&self->sub, self->unk_A8, self->unk_AC);
    result1 = func_ov104_0229d8a8(self, value);
    result2 = func_ov104_0229d858(self, value);
    func_ov002_02209d38(&self->sub, result1, result2, arg3);
    func_ov002_02209d8c(&self->sub);
    func_ov104_0229d500(self);
    func_ov002_02208098(self, 0x15);
}
