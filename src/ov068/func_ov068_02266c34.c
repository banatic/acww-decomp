/* func_ov068_02266c34 @ 0x02266c34, 0x3a bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    short unk_14;
} UnkStruct_02266c34;

extern void func_ov068_02266be4(UnkStruct_02266c34 *out, int a, int b, int c, int d, int e, int f, int g, unsigned char h);

void func_ov068_02266c34(UnkStruct_02266c34 *out, int a, int b, int c, int d, int e, int f, int g, unsigned char h)
{
    out->unk_00 = 1;
    func_ov068_02266be4(out, a, b, c, d, e, f, g, h);
    out->unk_04 = 3;
    out->unk_0C = -1;
    out->unk_10 = -1;
    out->unk_14 = 0;
}
