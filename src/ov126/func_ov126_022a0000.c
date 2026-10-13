/* func_ov126_022a0000 @ 0x022a0000, 0x54 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov126_0229f7a8(char *, int);
extern void func_ov095_02299aec(char *);
extern int func_ov095_02299b7c(char *);
extern int func_ov095_02299b38(char *);
extern void func_ov002_0220a0b4(char *, int, int);
extern void func_ov002_0220a374(char *, int);
extern void func_ov126_0229fea0(char *);

void func_ov126_022a0000(char *arg0)
{
    int val;
    int val2;

    func_ov126_0229f7a8(arg0, 0x80);
    func_ov095_02299aec(arg0 + 0x19c);
    val = func_ov095_02299b7c(arg0 + 0x19c);
    val2 = func_ov095_02299b38(arg0 + 0x19c);
    func_ov002_0220a0b4(arg0 + 0x3f90, val, val2);
    func_ov002_0220a374(arg0 + 0x3f90, 1);
    func_ov126_0229fea0(arg0);
}
