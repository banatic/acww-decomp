/* func_ov100_0229cd10 @ 0x0229cd10, 0x3c bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x2918];
    unsigned short unk_2918;
    unsigned char pad_291A[2];
    unsigned char unk_291C;
    unsigned char unk_291D;
} UnkStruct_0229cd10;

extern void func_ov100_0229cd7c(UnkStruct_0229cd10 *, int);
extern void func_ov100_0229d4a8(UnkStruct_0229cd10 *, int, unsigned short, unsigned char);

void func_ov100_0229cd10(UnkStruct_0229cd10 *a, int b)
{
    if (a->unk_291D == 1) {
        unsigned short h = a->unk_2918;
        unsigned char c = a->unk_291C;
        func_ov100_0229cd7c(a, b);
        func_ov100_0229d4a8(a, b, h, c);
    }
}
