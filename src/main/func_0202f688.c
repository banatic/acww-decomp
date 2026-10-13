/* func_0202f688 @ 0x0202f688, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int FX_MulFunc(int, int);

typedef struct {
    int pad_00;
    int unk_04;
    int unk_08;
    int pad_0C;
    int pad_10;
    int unk_14;
    int unk_18;
} UnkStruct_0202f688;

int func_0202f688(UnkStruct_0202f688 *data)
{
    int a;
    int b;
    a = FX_MulFunc(data->unk_14, data->unk_04);
    b = FX_MulFunc(data->unk_18, data->unk_08);
    return -(a + b);
}
