/* func_ov120_0229b900 @ 0x0229b900, 0x7c bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern int func_ov002_02208054(void *arg, int n);
extern unsigned char *func_ov002_02208098(void *arg, unsigned char value);
extern void func_ov120_0229b604(void *arg);
extern int func_ov120_0229a9b4(void *arg);
extern int func_ov120_0229aacc(void *arg);
extern int func_ov120_0229aed8(void *arg);
extern int func_ov120_0229b100(void *arg);
extern void func_0208e95c(void *addr, int n);

void func_ov120_0229b900(void *arg)
{
    unsigned int flag;

    if (func_ov002_02208054(arg, 1) != 0) {
        func_ov120_0229b604(arg);
        return;
    }

    flag = (data_021fbdd8 != 0 && data_021fbddc != 0) ? 1 : 0;
    if (flag > 0) {
        if (func_ov120_0229a9b4(arg) != 0) {
            return;
        }
        if (func_ov120_0229aacc(arg) != 0) {
            func_0208e95c((char *) arg + 0x674, 2);
            func_ov002_02208098(arg, 1);
        } else {
            if (func_ov120_0229aed8(arg) != 0) {
                return;
            }
            if (func_ov120_0229b100(arg) != 0) {
                return;
            }
        }
    }
}
