/* func_ov146_0229adb8 @ 0x0229adb8, 0x3e bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229adb8 {
    unsigned char pad_00[0x94];
    int unk_94;
    unsigned char pad_98[0x0c];
    int unk_A4;
} UnkStruct_0229adb8;

extern void func_ov002_02207e80(UnkStruct_0229adb8 *self, int a, int b, int c);
extern int func_ov002_02207f60(UnkStruct_0229adb8 *self);
extern void func_ov146_02299b58(UnkStruct_0229adb8 *self);

void func_ov146_0229adb8(UnkStruct_0229adb8 *self)
{
    func_ov002_02207e80(self, 6, 0, 0);
    func_ov002_02207e80(self, 4, 0, 0x38 - self->unk_A4);
    self->unk_94 = func_ov002_02207f60(self);
    func_ov146_02299b58(self);
}
