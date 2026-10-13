/* func_ov068_02266be4 @ 0x02266be4, 0x38 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201ad18(void *a, int b, int c, int d, int e, int f, int g, unsigned char h);

struct UnkStruct_02266be4 {
    unsigned char pad_00[8];
    unsigned char unk_08;
};

void func_ov068_02266be4(struct UnkStruct_02266be4 *out, char *base, unsigned char p3, int p4, int p5, int p6, int p7, int p8,
                         unsigned char p9)
{
    func_0201ad18((void *) (base + 0x3b0), p3, p4, p5, p6, p7, p8, p9);
    out->unk_08 = p3;
}
