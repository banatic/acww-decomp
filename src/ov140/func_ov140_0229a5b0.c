/* func_ov140_0229a5b0 @ 0x0229a5b0, 0x64 bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov140_02299fb0(void *, int);
extern void func_ov140_02299f90(void *, int);
extern void func_ov002_0220a05c(void *, int, int, int, int);
extern void func_ov002_02208098(void *, int);

struct UnkStruct_0229a5b0 {
    char pad_00[0x8d];
    unsigned char unk_8D;
    char pad_8E[0x820];
    unsigned char unk_8AE;
    char pad_8AF[0x9dd];
    unsigned char huge;
};

void func_ov140_0229a5b0(struct UnkStruct_0229a5b0 *p, int a, int b)
{
    if (func_ov140_02299fb0(p, 0x10) != 0) {
        func_ov002_0220a05c(&p->huge, a, b, 3, 0);
        func_ov140_02299f90(p, 0x10);
    } else {
        func_ov002_0220a05c(&p->huge, a, b, 3, 1);
    }
    p->unk_8AE = p->unk_8D;
    func_ov002_02208098(p, 2);
}
