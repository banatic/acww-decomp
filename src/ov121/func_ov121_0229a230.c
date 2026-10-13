/* func_ov121_0229a230 @ 0x0229a230, 0x64 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char func_ov002_022090e4(void *p, int v);
extern int func_ov002_02208ae4(void *p);
extern int func_ov002_02208ad8(void *p, unsigned char v);
extern void func_ov002_0220a0b4(void *p, int a, int b);
extern void func_0208e4c0(void *p, int v);
extern void func_ov002_02208098(void *p, int v);

typedef struct Sub1 {
    int a;
} Sub1;
typedef struct Sub2 {
    int b;
} Sub2;

typedef struct Super {
    unsigned char pad_00[0xB2];
    unsigned char unk_B2;
    unsigned char unk_B3;
    unsigned char pad_B4[0x3A8 - 0xB4];
    Sub2 sub_3A8;
    unsigned char pad2[0x528 - (0x3A8 + sizeof(Sub2))];
    Sub1 sub_528;
} Super;

void func_ov121_0229a230(Super *self)
{
    int r4;

    self->unk_B2 = 8;
    self->unk_B3 = func_ov002_022090e4(&self->sub_528, 1);
    r4 = func_ov002_02208ae4(&self->sub_528);
    func_ov002_0220a0b4(&self->sub_3A8, r4, func_ov002_02208ad8(&self->sub_528, self->unk_B3));
    func_0208e4c0(&self->sub_3A8, 8);
    func_ov002_02208098(self, 15);
}
