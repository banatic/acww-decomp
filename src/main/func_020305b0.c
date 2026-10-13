/* func_020305b0 @ 0x020305b0, 0x90 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020305b0 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
} UnkStruct_020305b0_2;
typedef struct UnkStruct_020305b0_3 {
    int unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_020305b0_4;
extern int func_020ea990(UnkStruct_020305b0_2 *a, UnkStruct_020305b0_4 *b, int c);
extern int func_020ea838(int *vec);
extern int FX_MulFunc(int a, int b);
int func_020305b0(UnkStruct_020305b0_2 *a, UnkStruct_020305b0_4 *b, int c)
{
    int ret;
    int vec[3];
    int val;
    int overlap;
    ret = func_020ea990(a, b, c);
    if (ret < (c + a->unk_0C)) {
        if (b->unk_04 < (a->unk_04 + a->unk_10)) {
            val = b->unk_08 - a->unk_08;
            vec[0] = b->unk_00 - a->unk_00;
            vec[1] = 0;
            vec[2] = val;
            if (func_020ea838(vec) != 0) {
                overlap = (c + a->unk_0C) - ret;
                b->unk_00 += FX_MulFunc(vec[0], overlap);
                b->unk_08 += FX_MulFunc(vec[2], overlap);
                return 1;
            }
        }
        goto return0;
    } else {
        if (ret > ((c + a->unk_0C) + 0x200)) {
            goto return0;
        }
        if (b->unk_04 >= (a->unk_04 + a->unk_10)) {
            goto return0;
        }
        return 1;
    }
return0:
    return 0;
}
