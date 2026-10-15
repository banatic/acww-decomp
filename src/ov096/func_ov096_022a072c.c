/* func_ov096_022a072c @ 0x022a072c, 0x9c bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206f56c(void);
extern int func_ov002_02208014(void *self);
extern int func_ov002_02208008(void *self);
extern int func_ov096_0229c2fc(void *self, int param);
extern int func_ov002_02209044(void *p1, int val, void *p2, unsigned char b);
extern void func_ov096_0229d1a0(void *self);
extern void func_ov096_0229dd44(void *self);
extern void func_ov002_0220a1dc(void *p);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov096_0229dce0(void *self);

extern struct {
    unsigned short pad;
    unsigned short flags;
} data_021fbe40;

void func_ov096_022a072c(void *self)
{
    if (func_0206f56c()) {
        func_ov096_0229d1a0(self);
        return;
    }
    if (func_ov002_02208014(self)) {
        func_ov096_0229d1a0(self);
        return;
    }
    {
        int v = func_ov002_02208008(self);
        unsigned char b = (unsigned char) func_ov096_0229c2fc(self, 0x00040000);
        if (func_ov002_02209044((unsigned char *) self + 0x2564, v, (unsigned char *) self + 0xbc, b)) {
            func_ov096_0229dd44(self);
            return;
        }
        if (data_021fbe40.flags & 1) {
            func_ov002_0220a1dc((unsigned char *) self + 0x2500);
            func_ov002_02208098((void *) (self), 0xe);
        } else if (data_021fbe40.flags & 2) {
            func_ov096_0229dce0(self);
        }
    }
}
