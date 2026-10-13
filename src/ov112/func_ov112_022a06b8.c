/* func_ov112_022a06b8 @ 0x022a06b8, 0x58 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40;
extern int func_ov112_022a02f4(void *self, int flag);
extern void func_ov095_0229bf3c(void *p);
extern void func_ov002_02208098(void *self, int arg);
extern void func_ov112_0229f3e0(void *self);
extern void func_ov112_022a0028(void *self);

int func_ov112_022a06b8(unsigned char *self)
{
    if ((data_021fbe40 & 2) == 0) {
        return 0;
    }
    if (func_ov112_022a02f4(self, 0)) {
        func_ov095_0229bf3c(self + 0x384);
        self[0xc1] = self[0x8d];
        func_ov002_02208098(self, 11);
    } else {
        func_ov112_0229f3e0(self);
        func_ov112_022a0028(self);
    }
    return 1;
}
