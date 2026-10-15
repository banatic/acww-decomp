/* func_ov096_022a1160 @ 0x022a1160, 0x70 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206f56c(void);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_ov096_0229c2fc(void *arg, int val);
extern int func_ov096_0229ec4c(void *receiver);
extern void func_ov096_0229f9dc(void *arg, unsigned char byte);
extern void func_ov002_022096d8(void *ptr, int val);
extern int func_ov002_02207d24(void *ptr, int val);
extern unsigned char data_021fbdd8;

void func_ov096_022a1160(unsigned char *arg)
{
    if (func_0206f56c() != 0) {
        func_ov002_02208098((void *) (arg), 4);
        return;
    }
    if (data_021fbdd8 == 0) {
        func_ov002_02208098((void *) (arg), 4);
        return;
    }
    if (func_ov096_0229c2fc(arg, 4) == 0) {
        return;
    }
    if (func_ov096_0229ec4c(arg) == 0) {
        return;
    }
    func_ov096_0229f9dc(arg, arg[0xb2]);
    func_ov002_022096d8(arg + 0x2564, 0);
    func_ov002_02207d24(arg + 0x2418, 1);
}
