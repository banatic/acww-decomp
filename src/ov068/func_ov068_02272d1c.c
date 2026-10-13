/* func_ov068_02272d1c @ 0x02272d1c, 0x40 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int FX_Div(int, int);

typedef struct {
    char pad_00[0x2cc];
    int unk_2CC;
    int unk_2D0;
    int unk_2D4;
} InputStruct;

void func_ov068_02272d1c(int *out, InputStruct *in)
{
    out[0] = in->unk_2CC;
    out[1] = in->unk_2D0;
    out[2] = in->unk_2D4;
    out[0] += FX_Div(0x19000, 0x64000) - 0xf6;
}
