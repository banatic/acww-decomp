/* func_02089c20 @ 0x02089c20, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02089c20 {
    char pad_00[0x40];
    int unk_40;
};

extern void func_0208a000(struct UnkStruct_02089c20 *p, int b, int c, int d, int e, int f, unsigned char g, int h);

void func_02089c20(struct UnkStruct_02089c20 *p, int a, int b, int c, int d, int e, int f, unsigned char g, int h)
{
    p->unk_40 = a;
    func_0208a000(p, b, c, d, e, f, g, h);
}
