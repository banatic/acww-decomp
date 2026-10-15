/* func_ov096_022a1058 @ 0x022a1058, 0xc0 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_02208e28(const unsigned char *p);
extern int func_0206f56c(void);
extern int func_ov002_02208054(const unsigned char *p, int n);
extern int func_ov002_02208b00(const unsigned char *p, int a, int b);
extern int func_ov096_0229c2fc(const unsigned char *p, int n);
extern int func_ov096_0229d0e4(const unsigned char *p);
extern void func_ov002_02209114(const unsigned char *p, int a, int b);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov096_0229d1a0(const unsigned char *p);
extern unsigned char data_021fbdd8, data_021fbddc, data_021f6c58, data_021f6c54;

void func_ov096_022a1058(unsigned char *self)
{
    void *res;
    int r4, t;
    unsigned int flag;
    unsigned char *p;

    res = func_ov002_02208e28(self + 0x2564);
    if (res == 0) {
        return;
    }
    if (func_0206f56c() != 0) {
        func_ov096_0229d1a0(self);
        return;
    }
    if (func_ov002_02208054(self, 1) != 0) {
        func_ov096_0229d1a0(self);
        return;
    }
    flag = (data_021fbdd8 != 0 && data_021fbddc != 0);
    if (flag != 0) {
        r4 = func_ov002_02208b00(self + 0x2564, data_021f6c58, data_021f6c54);
        if (r4 < 0) {
            return;
        }
        if (func_ov096_0229c2fc(self, 0x40000) != 0 && r4 == 0) {
            return;
        }
        p = self + r4;
        self[0xbb] = p[0x2951];
        t = func_ov096_0229d0e4(self);
        func_ov002_02209114(self + 0x2564, r4, t);
        func_ov002_02208098((void *) (self), 0x1e);
    }
}
