/* func_ov117_02299a48 @ 0x02299a48, 0x40 bytes, Thumb, module ov117
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov117_02299a18(void);
extern void func_ov117_022999fc(int);
extern void func_ov117_022999e0(int);
extern void func_ov117_022999a0(int, int);

void func_ov117_02299a48(int a, int b)
{
    int r5 = a;
    int r4 = b;
    func_ov117_02299a18();
    func_ov117_022999fc(0);
    func_ov117_022999fc(1);
    func_ov117_022999fc(2);
    func_ov117_022999fc(3);
    func_ov117_022999e0(0);
    func_ov117_022999e0(1);
    func_ov117_022999a0(r5, r4);
}
