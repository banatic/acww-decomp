/* func_ov121_0229a294 @ 0x0229a294, 0x50 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208ae4(void *p);
extern int func_ov002_02208ad8(void *p, unsigned char c);
extern int func_ov002_0220a08c(void *p, int a, int b, int c);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);

typedef struct {
    char pad_00[0x8d];
    unsigned char unk_8D;
    char pad_8E[0xb3 - 0x8e];
    unsigned char unk_B3;
    unsigned char unk_B4;
    char pad_B5[0x3a8 - 0xb5];
    char unk_3A8;
    char pad_3A9[0x528 - 0x3a9];
    char unk_528;
} UnkStruct_0229a294;

void func_ov121_0229a294(UnkStruct_0229a294 *self)
{
    int v1, v2;
    v1 = func_ov002_02208ae4(&self->unk_528);
    v2 = func_ov002_02208ad8(&self->unk_528, self->unk_B3);
    func_ov002_0220a08c(&self->unk_3A8, v1, v2, 2);
    self->unk_B4 = self->unk_8D;
    func_ov002_02208098(self, 6);
}
