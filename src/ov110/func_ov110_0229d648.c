/* func_ov110_0229d648 @ 0x0229d648, 0x38 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229d648 {
    char pad_00[0xA8];
    int unk_A8;
    int unk_AC;
} UnkStruct_0229d648;

extern void func_ov110_0229cd14(void *a, void *b);
extern int func_ov110_0229d3d8(void *a, void *b);
extern int func_ov110_0229d388(void *a, void *b);
extern unsigned char *func_ov110_0229d6c4(void *a, int b, int c);

void func_ov110_0229d648(UnkStruct_0229d648 *p, void *q, int n)
{
    func_ov110_0229cd14(p, q);
    p->unk_A8 = func_ov110_0229d3d8(p, q);
    p->unk_AC = func_ov110_0229d388(p, q);
    func_ov110_0229d6c4(p, n, 4);
}
