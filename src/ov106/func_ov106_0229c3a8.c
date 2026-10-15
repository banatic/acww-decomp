/* func_ov106_0229c3a8 @ 0x0229c3a8, 0x70 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229c3a8;
extern void func_ov106_0229cd88(struct UnkStruct_0229c3a8 *self, unsigned char b);
extern int func_ov106_0229d170(struct UnkStruct_0229c3a8 *self, unsigned char b);
extern int func_ov106_0229d128(struct UnkStruct_0229c3a8 *self, unsigned char b);
extern int func_0206fe54(void);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov094_0229b1d8(void *addr);

struct UnkStruct_0229c3a8 {
    char pad_00[0xac];
    int unk_AC;
    int unk_B0;
    char pad_B4[5];
    unsigned char unk_B9;
};

void func_ov106_0229c3a8(struct UnkStruct_0229c3a8 *self)
{
    unsigned char b;
    b = self->unk_B9;
    func_ov106_0229cd88(self, b);
    self->unk_AC = func_ov106_0229d170(self, b);
    self->unk_B0 = func_ov106_0229d128(self, b);
    if (func_0206fe54() != 0) {
        self->unk_AC -= 2;
        self->unk_B0 -= 2;
    }
    func_ov002_02208098((void *) (self), 0x26);
    func_ov094_0229b1d8((char *) self + 0x0b58);
}
