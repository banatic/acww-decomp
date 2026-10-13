/* func_0200a528 @ 0x0200a528, 0x90 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x2d8];
    unsigned int unk_2D8;
    char pad_2DC[0x428];
    int unk_704;
    char pad_708[0x128];
    int unk_830;
    int unk_834;
    int unk_838;
} UnkStruct_0200a528;

extern void func_0200f268(UnkStruct_0200a528 *s, int n);
extern void func_0200f650(UnkStruct_0200a528 *s, int n);
extern int _s32_div_f(unsigned int a, int b);

void func_0200a528(UnkStruct_0200a528 *s)
{
    if (s->unk_704 == 0x18) {
        goto equal;
    }
    s->unk_830 = 0;
    s->unk_834 = 0;
    s->unk_838 = 0;
    func_0200f268(s, 13);
    goto end;
equal: {
    unsigned int t = (s->unk_2D8 << 4) >> 16;
    if (t < 6) {
        int r4 = 0x1000 - _s32_div_f(t << 12, 6);
        if (r4 < 0) {
            r4 = 0;
            func_0200f268(s, 13);
        }
        s->unk_830 = r4;
        s->unk_834 = r4;
        s->unk_838 = r4;
        func_0200f650(s, r4);
    } else {
        s->unk_830 = 0;
        s->unk_834 = 0;
        s->unk_838 = 0;
    }
}
end:;
}
