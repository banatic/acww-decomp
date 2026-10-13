/* func_ov127_022998b4 @ 0x022998b4, 0x10c bytes, Thumb, module ov127
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022998b4 {
    char pad_00[0x2824];
    short unk_2824;
    short unk_2826;
    char pad_2828[2];
    short unk_282A;
    short unk_282C;
};

extern void func_ov127_02299868(struct UnkStruct_022998b4 *p, int flag);
extern void func_ov127_02299858(struct UnkStruct_022998b4 *p, int flag);
extern void func_020eaca0(int *out, int *a, int *b);
extern int func_020ea9c8(int *vec);
extern int FX_MulFunc(int a, int b);
extern int FX_Div(int a, int b);
extern void func_01ffd070(int *out, int *a, int *b);

void func_ov127_022998b4(struct UnkStruct_022998b4 *p)
{
    int a[3];
    int b[3];
    int c[3];
    int d[3];
    int e[3];
    int diff, angle, mag;

    func_ov127_02299868(p, 1);

    a[1] = 0;
    a[0] = (int) p->unk_2824 << 12;
    a[2] = (int) p->unk_2826 << 12;

    diff = (int) p->unk_282A - (int) p->unk_2824;
    angle = (int) p->unk_282A;
    if (diff <= -256) {
        angle += 0x200;
    } else if (diff >= 256) {
        angle -= 0x200;
    }
    b[0] = angle << 12;
    b[1] = 0;
    b[2] = (int) p->unk_282C << 12;

    func_020eaca0(d, b, a);

    c[0] = d[0];
    c[1] = d[1];
    c[2] = d[2];

    mag = func_020ea9c8(c);

    if (mag <= 0x8000) {
        func_ov127_02299858(p, 4);
        p->unk_2824 = p->unk_282A;
        p->unk_2826 = p->unk_282C;
        return;
    }

    diff = mag >> 1;
    if (diff < 0x8000) {
        diff = 0x8000;
    } else if (diff > 0x40000) {
        diff = 0x40000;
    }

    c[0] = FX_Div(FX_MulFunc(c[0], diff), mag);
    c[2] = FX_Div(FX_MulFunc(c[2], diff), mag);

    func_01ffd070(e, a, c);

    b[0] = e[0];
    b[1] = e[1];
    b[2] = e[2];
    p->unk_2824 = b[0] >> 12;
    p->unk_2826 = b[2] >> 12;
}
