/* func_ov112_022a122c @ 0x022a122c, 0x78 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov095_0229bf7c(void *p, int n);
extern int func_ov112_0229fe70(void *p, int n);
extern void func_ov112_0229fc18(void *p);
extern void func_ov112_0229fe50(void *p, int n);
extern void func_ov112_0229fe60(void *p, int n);
extern void func_ov112_0229fbf0(void *p);
extern void func_ov112_0229fbc0(void *p);

void func_ov112_022a122c(void *self)
{
    func_ov095_0229bf7c((char *) self + 0x384, 6);
    if (func_ov112_0229fe70(self, 4)) {
        func_ov112_0229fc18(self);
        func_ov112_0229fe50(self, 4);
        func_ov112_0229fe60(self, 2);
    }
    if (func_ov112_0229fe70(self, 8)) {
        func_ov112_0229fe50(self, 8);
        func_ov112_0229fe60(self, 2);
    }
    if (func_ov112_0229fe70(self, 2)) {
        func_ov112_0229fbf0(self);
        func_ov112_0229fbc0(self);
        func_ov112_0229fe50(self, 2);
    }
}
