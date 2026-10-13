/* func_02032444 @ 0x02032444, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02032214(void *self, void *src1, short d, void *src2);

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
} SrcStruct;

typedef struct {
    unsigned char pad_00[4];
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1C;
    int unk_20;
    int unk_24;
    short unk_28;
    unsigned char pad_2A[0x98 - 0x2a];
    char unk_98;
} UnkStruct_02032444;

void func_02032444(UnkStruct_02032444 *out, int a, int b, int c, SrcStruct *src1, short d, SrcStruct *src2)
{
    out->unk_10 = a;
    out->unk_14 = b;
    out->unk_18 = c;
    func_02032214(out, src1, d, src2);
    out->unk_04 = src1->unk_00;
    out->unk_08 = src1->unk_04;
    out->unk_0C = src1->unk_08;
    out->unk_1C = src2->unk_00;
    out->unk_20 = src2->unk_04;
    out->unk_24 = src2->unk_08;
    out->unk_28 = d;
    out->unk_98 = 1;
}
