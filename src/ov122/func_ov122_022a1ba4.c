/* func_ov122_022a1ba4 @ 0x022a1ba4, 0x2e bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x8c];
    unsigned char unk_8C;
    char pad_8D[11];
    unsigned int unk_98;
} UnkStruct_022a1ba4;

extern int func_ov122_0229f444(UnkStruct_022a1ba4 *);
extern void func_ov122_022a1718(UnkStruct_022a1ba4 *);
extern void func_ov122_0229efd8(UnkStruct_022a1ba4 *, int);

void func_ov122_022a1ba4(UnkStruct_022a1ba4 *a)
{
    if (func_ov122_0229f444(a) == 0) {
        func_ov122_022a1718(a);
        func_ov122_0229efd8(a, 2);
        a->unk_98 = 0xc0;
        a->unk_8C = 7;
    }
}
