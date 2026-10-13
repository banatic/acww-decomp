/* func_ov121_0229a1e4 @ 0x0229a1e4, 0x4c bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xb3];
    unsigned char flag;
    unsigned char pad_B4[0x3a8 - 0xb3 - 1];
    char unk_3A8;
    unsigned char pad_3A9[0x528 - 0x3a8 - 1];
    char unk_528;
} UnkStruct_0229a1e4;

extern int func_ov002_02208ae4(void *ptr);
extern int func_ov002_02208ad8(void *ptr, int byte);
extern void func_ov002_0220a0b4(void *ptr, int a, int b);
extern void func_ov002_0220a374(void *ptr, int a);

void func_ov121_0229a1e4(UnkStruct_0229a1e4 *s)
{
    int v1;
    int v2;
    s->flag = 0;
    v1 = func_ov002_02208ae4(&s->unk_528);
    v2 = func_ov002_02208ad8(&s->unk_528, s->flag);
    func_ov002_0220a0b4(&s->unk_3A8, v1, v2);
    func_ov002_0220a374(&s->unk_3A8, 7);
}
