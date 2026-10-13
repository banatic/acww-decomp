/* func_0202f1cc @ 0x0202f1cc, 0x9a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203000c(void *b, void *a);
extern int FX_MulFunc(int, int);
extern long long func_01ffd028(void *b, int *vec);

struct UnkStruct_0202f1cc {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
};

struct UnkStruct_0202f1cc_2 {
    int pad_00;
    int pad_04;
    int pad_08;
    int pad_0C;
    int pad_10;
    int pad_14;
    int unk_18;
    int unk_1C;
    int unk_20;
};

int func_0202f1cc(struct UnkStruct_0202f1cc *a, int *out, struct UnkStruct_0202f1cc_2 *b)
{
    int tmp, sum1, sum2, fc;
    int d, e, f;
    int vec1[3];
    int vec2[3];
    long long res1, res2;

    fc = a->unk_0C;
    if (func_0203000c(b, a) <= fc) {
        tmp = a->unk_08 + FX_MulFunc(b->unk_20, a->unk_0C);
        sum1 = a->unk_04 + FX_MulFunc(b->unk_1C, a->unk_0C);
        sum2 = a->unk_00 + FX_MulFunc(b->unk_18, a->unk_0C);

        vec1[0] = sum2;
        vec1[1] = sum1;
        vec1[2] = tmp;

        d = a->unk_08 - tmp;
        e = a->unk_04 - sum1;
        f = a->unk_00 - sum2;
        vec2[0] = f;
        vec2[1] = e;
        vec2[2] = d;

        res1 = func_01ffd028(b, vec1);
        res2 = func_01ffd028(b, vec2);

        if (res1 < res2) {
            out[0] = vec1[0];
            out[1] = vec1[1];
            out[2] = vec1[2];
        } else {
            out[0] = vec2[0];
            out[1] = vec2[1];
            out[2] = vec2[2];
        }
        return 1;
    } else {
        return 0;
    }
}
