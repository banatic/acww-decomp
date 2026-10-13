/* func_ov135_0229d428 @ 0x0229d428, 0x54 bytes, Thumb, module ov135
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fe54(char *p);
extern void func_ov002_02209eb8(char *p);
extern int func_ov135_0229c574(char *p, int flag);
extern int func_ov002_02207f60(char *p);
extern void func_ov134_0229b220(char *p, int a, int b);
extern void func_ov002_0220ad18(char *p, int b);

int func_ov135_0229d428(char *self)
{
    int a;
    int b;

    if (func_0206fe54(self) != 0) {
        func_ov002_02209eb8(self + 0x98);
    }
    if (func_ov135_0229c574(self, 1) == 0) {
        return 0;
    }
    a = func_ov002_02207f60(self);
    func_ov134_0229b220(self + 0x2c8, 0, a);
    b = func_ov002_02207f60(self);
    func_ov002_0220ad18(self + 0xfc, b);
    return 1;
}
