/* func_02037f28 @ 0x02037f28, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1C;
    int unk_20;
    int unk_24;
} DST;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
} SRC;

extern void func_02037ecc(DST *dst, int a, int b, int c);

void func_02037f28(DST *dst, int p1, SRC *src, int p4, int p5, int p6, int p7, int p8, int p9, int p10, int p11)
{
    dst->unk_00 = p1;
    dst->unk_0C = src->unk_00;
    dst->unk_10 = src->unk_04;
    dst->unk_14 = src->unk_08;
    dst->unk_18 = p4;
    dst->unk_1C = p5;
    dst->unk_24 = p6;
    dst->unk_04 = p9;
    dst->unk_08 = p10;
    func_02037ecc(dst, p7, p8, p11);
}
