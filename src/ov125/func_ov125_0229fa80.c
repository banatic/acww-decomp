/* func_ov125_0229fa80 @ 0x0229fa80, 0x78 bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov125_0229f76c(void *self, int arg);
extern int func_ov125_0229fb34(void *self);
extern int func_ov125_0229fb1c(void *self);
extern void func_ov125_0229f74c(void *self, int arg);
extern void func_ov002_0220a0b4(void *addr, int a, int b);
extern void func_ov002_0220a05c(void *addr, int a, int b, int c, int d);
extern unsigned char *func_ov002_02208098(void *self, unsigned char value);

void func_ov125_0229fa80(unsigned char *self)
{
    if (func_ov125_0229f76c(self, 2)) {
        int a = func_ov125_0229fb34(self);
        int b = func_ov125_0229fb1c(self);
        func_ov002_0220a0b4(self + 0x644, a, b);
        func_ov125_0229f74c(self, 2);
    } else {
        int a = func_ov125_0229fb34(self);
        int b = func_ov125_0229fb1c(self);
        func_ov002_0220a05c(self + 0x644, a, b, 3, 1);
        self[0x87f] = self[0x8d];
        func_ov002_02208098(self, 5);
    }
}
