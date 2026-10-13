/* func_ov106_0229e4fc @ 0x0229e4fc, 0x48 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206f56c(void *);
extern int func_ov002_02208054(void *, int);
extern void func_ov002_02208098(void *, int);
extern int MATH_CalcMD5(void *);
extern void func_ov106_0229c418(void *);
extern void func_ov106_0229c458(void *);

void func_ov106_0229e4fc(void *arg)
{
    if (func_0206f56c(arg) != 0) {
        func_ov106_0229c418(arg);
        return;
    }
    if (func_ov002_02208054(arg, 1) != 0) {
        func_ov002_02208098(arg, 9);
        return;
    }
    if (MATH_CalcMD5((char *) arg + 0x2b3c) != 0) {
        func_ov106_0229c458(arg);
    }
}
