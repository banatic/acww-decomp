/* func_ov100_0229d69c @ 0x0229d69c, 0x3c bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov100_0229cd7c(void *a, int b, int c);
extern int func_ov100_0229d42c(void *a, int b);
extern int func_ov100_0229d3d8(void *a, int b);
extern void func_ov100_0229d71c(void *a, int b, int c);

struct UnkStruct_0229d69c {
    char pad_00[0x28d4];
    int unk_28D4;
    int unk_28D8;
};

void func_ov100_0229d69c(struct UnkStruct_0229d69c *a0, int a1, int a2)
{
    func_ov100_0229cd7c(a0, a1, a2);
    a0->unk_28D4 = func_ov100_0229d42c(a0, a1);
    a0->unk_28D8 = func_ov100_0229d3d8(a0, a1);
    func_ov100_0229d71c(a0, a2, 4);
}
