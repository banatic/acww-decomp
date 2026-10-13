/* func_ov133_0229ae94 @ 0x0229ae94, 0x3e bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x9c];
    unsigned char unk_9C;
    unsigned char unk_9D;
    unsigned char unk_9E;
    char unk_9F;
    unsigned char unk_A0;
} UnkStruct_0229ae94;

extern void func_ov133_0229ae1c(UnkStruct_0229ae94 *self);
extern void func_ov133_0229adb8(UnkStruct_0229ae94 *self, unsigned char b);
extern void func_ov133_0229b3f8(UnkStruct_0229ae94 *self, int n);

void func_ov133_0229ae94(UnkStruct_0229ae94 *self)
{
    func_ov133_0229ae1c(self);
    self->unk_A0 = self->unk_9C;
    func_ov133_0229adb8(self, self->unk_A0);
    self->unk_9D = 0xd;
    self->unk_9E = 0x5;
    func_ov133_0229b3f8(self, 1);
}
