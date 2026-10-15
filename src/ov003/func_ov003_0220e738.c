/* func_ov003_0220e738 @ 0x0220e738, 0x50 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_02010f5c(int argument0);
extern int func_020912d4(int, int, int, int);
extern void func_02091278(int, int, int, int);
extern void func_0200f2a0(int, int, int);

void func_ov003_0220e738(int *arg0)
{
    int *r4;
    int r0;
    int r1;
    int r2;
    int r3;
    int r5;

    r5 = (int) arg0;
    func_02010f5c(r5);
    r4 = (int *) (r5 + 0x7dc);
    r0 = *r4;
    r2 = 0;
    r1 = -1;
    if (r0 == r1) {
        r0 = 0x4c;
        r1 = r5 + 0x6e0;
        r3 = r2;
        r0 = func_020912d4(r0, r1, r3, r2);
        *r4 = r0;
    } else {
        r1 = r5 + 0x6e0;
        r3 = r2;
        func_02091278(r0, r1, r3, r2);
    }
    r0 = r5;
    r1 = 0x8a;
    r5 += 0x5c;
    r2 = r5;
    func_0200f2a0(r0, r1, r2);
}
