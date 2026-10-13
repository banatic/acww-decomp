/* func_ov106_0229cea8 @ 0x0229cea8, 0x64 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229cea8 {
    char pad_00[0xb6];
    unsigned char unk_B6;
    char pad_B7;
    unsigned char unk_B8;
    char pad_B9[0x20ff];
    char target[1];
};

extern int func_ov106_0229d3a0(struct UnkStruct_0229cea8 *self, unsigned char b);
extern int func_ov106_0229d390(struct UnkStruct_0229cea8 *self, unsigned char b);
extern int func_ov106_0229d090(struct UnkStruct_0229cea8 *self, unsigned char b);
extern void func_ov002_02207cf0(void *p);
extern void func_ov002_02207cf8(void *p);

void func_ov106_0229cea8(struct UnkStruct_0229cea8 *self)
{
    if (func_ov106_0229d3a0(self, self->unk_B8) != 0 || func_ov106_0229d390(self, self->unk_B8) != 0) {
        if (func_ov106_0229d090(self, self->unk_B8) != 0) {
            func_ov002_02207cf0(self->target);
        } else {
            self->unk_B6 = self->unk_B8;
            func_ov002_02207cf8(self->target);
        }
    } else {
        func_ov002_02207cf0(self->target);
    }
}
