/* func_ov101_0229ca58 @ 0x0229ca58, 0x54 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov101_0229ce38(void *self, unsigned char b);
extern int func_ov101_0229cc20(void *self, unsigned char b);
extern void func_ov002_02207cf0(void *p);
extern void func_ov002_02207cf8(void *p);

struct UnkStruct_0229ca58 {
    char pad_00[0xB1];
    unsigned char unk_B1;
    char pad_B2[1];
    unsigned char unk_B3;
    char pad_B4[0x2100];
    char unk_21B4;
};

void func_ov101_0229ca58(struct UnkStruct_0229ca58 *self)
{
    if (func_ov101_0229ce38(self, self->unk_B3)) {
        if (func_ov101_0229cc20(self, self->unk_B3)) {
            func_ov002_02207cf0(&self->unk_21B4);
        } else {
            self->unk_B1 = self->unk_B3;
            func_ov002_02207cf8(&self->unk_21B4);
        }
    } else {
        func_ov002_02207cf0(&self->unk_21B4);
    }
}
