/* func_ov107_0229cce8 @ 0x0229cce8, 0x34 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov107_0229cec4(void *argument0);
extern int func_ov107_0229ceb4(int);
extern void func_ov002_0220a0b4(int, int, int);
extern void func_ov002_0220a374(int, int);

void func_ov107_0229cce8(int arg0)
{
    int local_0;
    int r4;
    int r5;
    int r2;

    r5 = arg0;
    r4 = func_ov107_0229cec4((void *) arg0);
    r2 = func_ov107_0229ceb4(r5);
    func_ov002_0220a0b4(r5 + 0x22b4, r4, r2);
    func_ov002_0220a374(r5 + 0x22b4, 1);
}
