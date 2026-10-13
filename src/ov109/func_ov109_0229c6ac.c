/* func_ov109_0229c6ac @ 0x0229c6ac, 0x4c bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229c6ac {
    char pad_00[0x2274];
    int unk_2274;
    char pad_2278[0x22d8 - 0x2274 - 4];
    int unk_22D8;
    char pad_22DC[0x29d8 - 0x22d8 - 4];
    unsigned char unk_29D8;
} UnkStruct_0229c6ac;

extern int func_ov002_02208ae4(int *a, int b);
extern int func_ov002_02208ad8(int *a, int b);
extern void func_ov002_0220a0b4(int *a, int b, int c);
extern void func_ov002_0220a374(int *a, int b);

void func_ov109_0229c6ac(UnkStruct_0229c6ac *p)
{
    int ret1;
    int ret2;

    p->unk_29D8 = 0;
    ret1 = func_ov002_02208ae4(&p->unk_22D8, 0);
    ret2 = func_ov002_02208ad8(&p->unk_22D8, p->unk_29D8);
    func_ov002_0220a0b4(&p->unk_2274, ret1, ret2);
    func_ov002_0220a374(&p->unk_2274, 7);
}
