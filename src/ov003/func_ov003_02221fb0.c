/* func_ov003_02221fb0 @ 0x02221fb0, 0xf4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x18];
    char unk_18[4];
    int unk_1C;
    char pad_20[0x10];
    int unk_30;
    int unk_34;
    int unk_38;
    char pad_3C[0x10];
    short unk_4C;
    char pad_4E[2];
    short unk_50;
    short unk_52;
} UnkStruct_02221fb0;

extern void VEC_Add(void *a, void *b, void *c);
extern void func_ov003_0222da78(void *a);
extern void func_ov003_0222284c(UnkStruct_02221fb0 *s);

void func_ov003_02221fb0(UnkStruct_02221fb0 *s)
{
    switch (s->unk_4C) {
        case 0:
            s->unk_34 -= 0x400;
            VEC_Add(&s->unk_18, &s->unk_30, &s->unk_18);
            if (s->unk_1C < 0) {
                s->unk_1C = 0;
                s->unk_30 = 0;
                s->unk_34 = 0x1000;
                s->unk_38 = 0;
                s->unk_4C = 1;
            }
            break;
        case 1:
            s->unk_34 -= 0x400;
            VEC_Add(&s->unk_18, &s->unk_30, &s->unk_18);
            if (s->unk_1C < 0) {
                s->unk_1C = 0;
                s->unk_30 = 0;
                s->unk_34 = 0;
                s->unk_38 = 0;
                s->unk_4C = 2;
                s->unk_50 = 0x14;
            }
            break;
        case 2:
            s->unk_50 = (short) (s->unk_50 - 1);
            if (s->unk_50 < 0) {
                func_ov003_0222da78(&s->unk_18);
                s->unk_50 = 0x1e;
                s->unk_4C = 3;
            }
            break;
        case 3:
            s->unk_50 = (short) (s->unk_50 - 1);
            if (s->unk_50 < 0) {
                s->unk_4C = 4;
            }
            break;
        default:
            s->unk_52 = (short) (s->unk_52 - 1);
            if (s->unk_52 < 0) {
                func_ov003_0222284c(s);
            }
            break;
    }
}
