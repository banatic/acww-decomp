/* func_ov096_022a0c28 @ 0x022a0c28, 0x90 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206f56c(void);
extern int func_ov096_022a18dc(char *, int);
extern void func_ov094_02299c74(char *, int);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_ov096_0229ec38(char *, int);
extern void func_ov096_0229fa44(char *, int);
extern void func_ov096_0229f9dc(char *, int);
extern void func_ov096_0229c2ec(char *, int);
extern unsigned char data_021fbdd8;

void func_ov096_022a0c28(char *self)
{
    if (func_0206f56c()) {
        func_ov096_022a18dc(self, 7);
        func_ov094_02299c74(self + 0xde0, 0);
        return;
    } else {
        if (data_021fbdd8 == 0) {
            func_ov002_02208098((void *) (self), 0);
            func_ov094_02299c74(self + 0xde0, 0);
            return;
        } else {
            if (func_ov096_0229ec38(self, 4) == 0) {
                return;
            }
            func_ov096_0229fa44(self, 0x25);
            *(int *) (self + 0x9c) = -8;
            *(int *) (self + 0xa0) = -8;
            func_ov096_0229f9dc(self, 0x25);
            func_ov096_0229c2ec(self, 0x4000);
            func_ov094_02299c74(self + 0xde0, *(unsigned char *) (self + 0xbf));
        }
    }
}
