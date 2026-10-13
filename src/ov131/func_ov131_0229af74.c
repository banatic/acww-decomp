/* func_ov131_0229af74 @ 0x0229af74, 0x48 bytes, Thumb, module ov131
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov131_0229afe8(void *);
extern int func_ov131_0229afd8(void *);
extern void func_ov131_0229af40(void *, int, int);
extern int func_ov130_0229a124(void *);
extern void func_ov002_0220a314(void *);
extern void func_ov002_0220a2b4(void *);

void func_ov131_0229af74(void *r0)
{
    int r4;
    int r5;
    int r2;
    int r0_2;

    r4 = (int) r0;
    if (func_ov130_0229a124((void *) (r4 + 0x2c4)) != 0) {
        func_ov002_0220a314((void *) (r4 + 0x94));
    } else {
        func_ov002_0220a2b4((void *) (r4 + 0x94));
    }
    r5 = func_ov131_0229afe8((void *) r4);
    r2 = func_ov131_0229afd8((void *) r4);
    func_ov131_0229af40((void *) r4, r5, r2);
}
