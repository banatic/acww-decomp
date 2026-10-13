/* func_020bf308 @ 0x020bf308, 0xc0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int FX_MulFunc(int, int);
extern int _s32_div_f(int, int);
typedef struct UnkStruct_020bf308 {
    unsigned char pad_00[0x34];
    int unk_34;
    int unk_38;
    unsigned char pad1[0x4c - 0x3c];
    int unk_4C;
    int unk_50;
} UnkStruct_020bf308;
typedef struct Elem {
    unsigned char pad_00[0x4];
    int type;
    unsigned char pad1[0x2f - 0x8];
    unsigned char flag2f;
    unsigned char flag30;
    unsigned char pad_31[0x34 - 0x31];
    int unk_34;
    int unk_38;
    unsigned char pad_3C[0x44 - 0x3c];
    int unk_44;
    unsigned char pad_48[0x74 - 0x48];
} Elem;
extern Elem data_021f9a3c[];
extern Elem data_021f9fac[];
int func_020bf308(UnkStruct_020bf308 *self, int a, int b, int c)
{
    int val;
    int v1;
    int v2;
    int v3;
    int r;
    int s;
    int cx;
    int cy;
    int min_x;
    int max_x;
    int min_y;
    int val2;
    int result;
    int h;
    int left;
    int top;
    int bottom;
    int max_y;
    int right;
    Elem *p;
    v1 = FX_MulFunc(a, self->unk_4C);
    v2 = FX_MulFunc(b, self->unk_50);
    v3 = FX_MulFunc(c, self->unk_50);
    r = _s32_div_f(v1, 2);
    s = _s32_div_f(v2, 2);
    cy = self->unk_38 + v3;
    cx = self->unk_34;
    min_x = cx - r;
    val2 = cy - s;
    max_x = cx + r;
    min_y = val2;
    max_y = cy + s;
    p = data_021f9a3c;
    result = 0;
    while (p < data_021f9fac) {
        if ((p->type == 2) && (p->flag2f != 0)) {
            h = p->unk_44;
            if (h < 0) {
                h = -h;
            }
            left = p->unk_34 - 0x1000;
            top = p->unk_38 - 0x1000;
            val = 0x1000;
            bottom = (p->unk_38 + val) + h;
            right = p->unk_34 + val;
            if ((((min_x <= right) && (max_x >= left)) && (min_y <= bottom)) && (max_y >= top)) {
                result = 1;
                p->flag30 = 1;
            }
        }
        p++;
    }

    return result;
}
