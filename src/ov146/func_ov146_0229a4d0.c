/* func_ov146_0229a4d0 @ 0x0229a4d0, 0x64 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov146_02299670(void *self, int a);
extern void func_ov002_0220a05c(void *p, int a, int b, int c, int d);
extern void func_ov146_02299650(void *self, int a);
extern unsigned char *func_ov002_02208098(void *self, unsigned char value);

void func_ov146_0229a4d0(void *self, int a, int b)
{
    if (func_ov146_02299670(self, 0x20)) {
        func_ov002_0220a05c((char *) self + 0x15cc, a, b, 3, 0);
        func_ov146_02299650(self, 0x20);
    } else {
        func_ov002_0220a05c((char *) self + 0x15cc, a, b, 3, 1);
    }
    ((unsigned char *) self)[0xb3] = ((unsigned char *) self)[0x8d];
    func_ov002_02208098(self, 6);
}
