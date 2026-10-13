/* func_ov131_0229aff8 @ 0x0229aff8, 0x54 bytes, Thumb, module ov131
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov131_0229afe8(void *p);
extern int func_ov131_0229afd8(void *p);
extern void func_ov002_0220a0b4(void *p, int a, int b);
extern int func_ov130_0229a124(void *p);
extern void func_ov002_0220a374(void *p, int n);
extern void func_ov131_0229af24(void *p);

void func_ov131_0229aff8(void *p)
{
    int a;
    int b;

    a = func_ov131_0229afe8(p);
    b = func_ov131_0229afd8(p);
    func_ov002_0220a0b4((char *) p + 0x94, a, b);
    if (func_ov130_0229a124((char *) p + 0x2c4) != 0) {
        func_ov002_0220a374((char *) p + 0x94, 7);
    } else {
        func_ov002_0220a374((char *) p + 0x94, 1);
    }
    func_ov131_0229af24(p);
}
