/* func_02065604 @ 0x02065604, 0xa8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned short r : 5;
    unsigned short g : 5;
    unsigned short b : 5;
    unsigned short a : 1;
} Col;

typedef struct {
    char pad_00[0x50];
    int unk_50;
    char pad_54[0x16e - 0x54];
    Col unk_16E;
    Col unk_170;
    char pad_172[0x174 - 0x172];
    int unk_174;
} UnkStruct_02065604;

extern unsigned int data_021cd864;
extern int func_020b3658(int);
extern Col func_020bbf00(int);

short func_02065604(void)
{
    short s = 0;
    Col x;
    Col y;
    Col z;
    UnkStruct_02065604 *g;

    g = (UnkStruct_02065604 *) *(unsigned int *) &data_021cd864;
    if (g == 0) {
        return *(short *) &s;
    }

    switch (g->unk_50) {
        case 2:
        case 3: {
            int t = func_020b3658(g->unk_174);
            UnkStruct_02065604 *h = (UnkStruct_02065604 *) *(unsigned int *) &data_021cd864;
            int b1 = h->unk_170.b + ((t * (h->unk_16E.b - h->unk_170.b)) >> 12);
            int r1 = h->unk_170.r + ((t * (h->unk_16E.r - h->unk_170.r)) >> 12);
            int g1 = h->unk_170.g + ((t * (h->unk_16E.g - h->unk_170.g)) >> 12);
            *(unsigned short *) &z = (unsigned short) ((b1 << 10) | (r1 | (g1 << 5)));
            break;
        }
        default:
            x = func_020bbf00(2);
            y = x;
            z = y;
            break;
    }

    return *(short *) &z;
}
