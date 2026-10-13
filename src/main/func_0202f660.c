/* func_0202f660 @ 0x0202f660, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int FX_MulFunc(int, int);

struct s0 {
    char pad_00[0x14];
    int unk_14;
    int unk_18;
    int unk_1C;
};

struct s1 {
    int unk_00;
    int unk_04;
};

int func_0202f660(struct s0 *p0, struct s1 *p1)
{
    int v = p0->unk_1C;
    int a = FX_MulFunc(p0->unk_14, p1->unk_00);
    int b = FX_MulFunc(p0->unk_18, p1->unk_04);
    return (a + b) + v;
}
