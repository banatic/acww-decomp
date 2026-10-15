/* func_ov096_0229dc48 @ 0x0229dc48, 0x34 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229de0c(void *argument0);
extern int func_ov096_0229ddfc(int);
extern void func_ov002_0220a0b4(int, int, int);
extern void func_ov002_0220a374(int, int);

void func_ov096_0229dc48(int self)
{
    int r4;
    int r2;
    int r0;
    int r5 = self;

    r4 = func_ov096_0229de0c((void *) self);
    r0 = r5;
    r2 = func_ov096_0229ddfc(r0);
    r0 = r5 + 0x2500;
    func_ov002_0220a0b4(r0, r4, r2);
    r0 = r5 + 0x2500;
    func_ov002_0220a374(r0, 1);
}
