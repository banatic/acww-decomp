/* func_0203adc4 @ 0x0203adc4, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0203adc4 {
    int pad_00;
    int pad1;
    int unk_08;
} UnkStruct_0203adc4;

typedef struct Global {
    unsigned char pad_00[0x118];
    int unk_118;
    unsigned char pad1[0xd8];
    unsigned char unk_1F4;
    unsigned char pad_1F5[3];
    int unk_1F8;
    int unk_1FC;
} Global;

extern Global *data_021c67a4;

int func_0203adc4(UnkStruct_0203adc4 *a0, int unused, int b)
{
    Global *g;
    int mode;

    g = data_021c67a4;
    if (g != 0) {
        mode = g->unk_1F8;
        if (mode == 2 || mode == 4) {
            goto check;
        }
        if (mode != 1) {
            goto bottom;
        }
        if (g->unk_1FC == 2) {
            goto check;
        }
    bottom:
        if (g->unk_1F4 != 0) {
            goto check;
        }
        return 0;
    check:
        if (a0->unk_08 - (b >> 1) > g->unk_118 - 0x2000) {
            return 1;
        }
        return 0;
    }

    return 0;
}
