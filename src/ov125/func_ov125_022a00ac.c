/* func_ov125_022a00ac @ 0x022a00ac, 0x80 bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(void *self);
extern int func_ov002_02209044(void *a, int b, void *c, int d);
extern void func_ov002_0220a1dc(void *ptr);
extern unsigned char *func_ov002_02208098(void *self, unsigned char value);
void func_ov125_0229faf8(void *self);
void func_ov125_0229fa2c(void *self);
void func_ov125_0229f9c8(void *self);

struct Flags {
    char pad_00[2];
    unsigned short flag;
};
extern struct Flags data_021fbe40;

void func_ov125_022a00ac(void *self)
{
    if (func_ov002_02208014(self) != 0) {
        func_ov125_0229faf8(self);
        func_ov002_02208098(self, 1);
    } else {
        int val = func_ov002_02208008(self);
        if (func_ov002_02209044((char *) self + 0x180, val, (char *) self + 0x87e, 0) != 0) {
            func_ov125_0229fa2c(self);
        }
        if ((data_021fbe40.flag & 1) != 0) {
            func_ov002_0220a1dc((char *) self + 0x644);
            func_ov002_02208098(self, 4);
        } else {
            if ((data_021fbe40.flag & 2) != 0) {
                func_ov125_0229f9c8(self);
            }
        }
    }
}
