/* func_ov103_0229c6d4 @ 0x0229c6d4, 0x4c bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208ae4(const char *p);
extern int func_ov002_02208ad8(const char *p, int arg);
extern void func_ov002_0220a0b4(const char *p, int a, int b);
extern void func_ov002_0220a374(const char *p, int arg);

struct UnkStruct_0229c6d4 {
    char pad_00[0x2274];
    char unk_2274;
    char pad_2275[0x63];
    char unk_22D8;
    char pad_22D9[0xad0];
    unsigned char unk_2DA9;
};

void func_ov103_0229c6d4(struct UnkStruct_0229c6d4 *s)
{
    int a;
    s->unk_2DA9 = 0;
    a = func_ov002_02208ae4(&s->unk_22D8);
    func_ov002_0220a0b4(&s->unk_2274, a, func_ov002_02208ad8(&s->unk_22D8, s->unk_2DA9));
    func_ov002_0220a374(&s->unk_2274, 7);
}
