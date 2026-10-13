/* func_ov108_0229c5f4 @ 0x0229c5f4, 0x34 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov108_0229c7c8(void);
extern int func_ov108_0229c7b8(int);
extern void func_ov002_0220a0b4(int, int, int);
extern void func_ov002_0220a374(int, int);

void func_ov108_0229c5f4(int arg0)
{
    int local_0;
    int local_1;
    int local_2;

    local_0 = func_ov108_0229c7c8();
    local_1 = func_ov108_0229c7b8(arg0);
    func_ov002_0220a0b4(arg0 + 0x2498, local_0, local_1);
    func_ov002_0220a374(arg0 + 0x2498, 1);
}
