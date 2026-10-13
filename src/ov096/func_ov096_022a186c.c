/* func_ov096_022a186c @ 0x022a186c, 0x34 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov094_0229a1c0(void *);
extern void func_ov002_02208090(void *, int);
extern int func_ov096_0229c2fc(void *, unsigned int);
extern void func_ov096_022a1838(void *);

void func_ov096_022a186c(char *self)
{
    func_ov094_0229a1c0(self + 0xde0);
    func_ov002_02208090(self, 2);
    if (func_ov096_0229c2fc(self, 0x00080000) == 0) {
        func_ov096_022a1838(self);
    }
}
