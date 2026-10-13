/* func_0204b0c0 @ 0x0204b0c0, 0x9c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00, unk_04, unk_08;
} UnkStruct_0204b0c0;
typedef struct {
    int unk_00, unk_04;
} In2;
typedef struct {
    char pad_00[4];
    unsigned char unk_04, unk_05, unk_06, unk_07;
    unsigned short unk_08, unk_0A;
    unsigned short unk_0C;
    char pad_0E[0x20 - 0xe];
    int unk_20;
} Params;

void func_0204b0c0(UnkStruct_0204b0c0 *out, In2 *src, Params *p)
{
    out->unk_00 = src->unk_00;
    out->unk_04 = src->unk_04;

    if (out->unk_00 < 0) {
        out->unk_08 = -1;
        return;
    }

    {
        int local[6];
        int *lp;
        int sum;
        int i, maxv, maxi;
        unsigned char v7, v5, v4, v6;

        lp = local;
        for (i = 0; i < 6; i++) {
            *lp++ = 0;
        }
        {
            volatile unsigned char *pb = (volatile unsigned char *) p;
            v7 = pb[7];
            v5 = pb[5];
            v4 = pb[4];
            v6 = pb[6];
        }
        sum = v4 + v6 + v5 + v7;

        if (sum > 0xf) {
            local[0] = (sum - 0xf) * 2;
        } else if (sum < 0xc) {
            local[1] = (0xc - sum) * 2;
        }
        if ((int) p->unk_08 >= 3) {
            local[2] = p->unk_08 - 2;
        }
        if ((int) p->unk_0A >= 3) {
            local[3] = p->unk_0A - 2;
        }
        local[4] = p->unk_0C * 0xa;
        if (((p->unk_20 << 31) >> 31) != 0) {
            local[5] = 0x32;
        }

        maxv = -1;
        maxi = -1;
        lp = local;
        for (i = 0; i < 6; lp++, i++) {
            if (*lp > maxv) {
                maxv = *lp;
                maxi = i;
            }
        }
        out->unk_08 = maxi;
    }
}
