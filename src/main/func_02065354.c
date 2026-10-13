/* func_02065354 @ 0x02065354, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    unsigned short unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1C;
    int unk_20;
} UnkStruct_02065354;

void func_02065354(UnkStruct_02065354 *p)
{
    int v;

    p->unk_08 = 0;
    p->unk_0C = -0x1000;
    p->unk_10 = 0;
    p->unk_1C += p->unk_20;

    if (p->unk_18 == 0) {
        if (p->unk_1C >= 0x1000) {
            p->unk_1C = 0x1000;
            p->unk_20 = -0x333;
            p->unk_18 = 1;
        }
    } else {
        if (p->unk_1C < 0) {
            p->unk_1C = 0;
            p->unk_20 = 0;
            p->unk_00 = 9;
            p->unk_14 = 0;
        }
    }

    v = (9 * p->unk_1C) >> 12;
    p->unk_04 = (unsigned short) ((v << 10) | ((v << 5) | v));
}
