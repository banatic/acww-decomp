/* func_ov110_0229cb28 @ 0x0229cb28, 0x50 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x8d];
    unsigned char unk_8D;
    unsigned char pad_8E[0xf8 - 0x8d - 1];
    unsigned char unk_F8;
    unsigned char pad_F9[0xfa - 0xf8 - 1];
    unsigned char unk_FA;
    unsigned char pad_FB[0x22e0 - 0xfa - 1];
    char unk_22E0[1];
    unsigned char pad_22E1[0x2344 - 0x22e0 - 1];
    char unk_2344[1];
} UnkStruct_0229cb28;

extern int func_ov002_02208ae4(void *ptr);
extern int func_ov002_02208ad8(void *ptr, unsigned char b);
extern void func_ov002_0220a08c(void *ptr, int a, int b, int c);
extern void func_ov002_02208098(void *ptr, int n);

void func_ov110_0229cb28(UnkStruct_0229cb28 *self)
{
    int tmp1;
    int tmp2;
    tmp1 = func_ov002_02208ae4(&self->unk_2344);
    tmp2 = func_ov002_02208ad8(&self->unk_2344, self->unk_FA);
    func_ov002_0220a08c(&self->unk_22E0, tmp1, tmp2, 2);
    self->unk_F8 = self->unk_8D;
    func_ov002_02208098(self, 8);
}
