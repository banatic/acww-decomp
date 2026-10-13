/* func_ov104_0229ec4c @ 0x0229ec4c, 0x74 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov104_0229d8f8(void *ptr, unsigned char b);
extern void func_020664a8(int arg);
extern void func_0206e230(void *ptr, int a, int b, int c, int d);
extern void func_ov002_02207f20(void *ptr, int a, int b, int c, int d);
extern void func_02002708(int arg);
extern void func_ov104_0229eb88(void *ptr);
extern void func_ov002_02208090(void *ptr, int arg);
extern void func_ov002_0220b53c(void *ptr, int arg);
extern void func_ov104_0229c354(void *ptr, int arg);

typedef struct {
    unsigned char pad_00[0xB9];
    unsigned char unk_B9;
    unsigned char pad_BA[0x2A14 - 0xB9 - 1];
    char unk_2A14[1];
    unsigned char pad_2A15[0x2D3C - 0x2A14 - 1];
    char unk_2D3C[1];
} UnkStruct_0229ec4c;

void func_ov104_0229ec4c(UnkStruct_0229ec4c *param)
{
    int a;
    a = func_ov104_0229d8f8(param, param->unk_B9);
    func_020664a8(a);
    func_0206e230(param->unk_2A14, a, 3, 4, 1);
    func_ov002_02207f20(param, 3, 0, 0, 0x30);
    func_02002708(3);
    func_02002708(4);
    func_ov104_0229eb88(param);
    func_ov002_02208090(param, 8);
    func_ov002_0220b53c(param->unk_2D3C, 0x88);
    func_ov104_0229c354(param, 0x80);
}
