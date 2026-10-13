/* func_ov106_0229d4ac @ 0x0229d4ac, 0x38 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov106_0229cd88(void *self, int a, int b);
extern int func_ov106_0229d170(void *self, int a);
extern int func_ov106_0229d128(void *self, int a);
extern void func_ov106_0229d518(void *self, int a, int b);

struct UnkStruct_0229d4ac {
    unsigned char pad_00[0xac];
    int unk_AC;
    int unk_B0;
};

void func_ov106_0229d4ac(struct UnkStruct_0229d4ac *self, int a, int b)
{
    func_ov106_0229cd88(self, a, b);
    self->unk_AC = func_ov106_0229d170(self, a);
    self->unk_B0 = func_ov106_0229d128(self, a);
    func_ov106_0229d518(self, b, 4);
}
