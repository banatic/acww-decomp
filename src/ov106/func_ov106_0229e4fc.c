/* func_ov106_0229e4fc @ 0x0229e4fc, 0x48 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206f56c(void);
extern int func_ov002_02208054(void *, int);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_ov002_0220b498(void *object);
extern void func_ov106_0229c418(void *);
extern void func_ov106_0229c458(void *);

void func_ov106_0229e4fc(void *arg)
{
    if (func_0206f56c() != 0) {
        func_ov106_0229c418(arg);
        return;
    }
    if (func_ov002_02208054(arg, 1) != 0) {
        func_ov002_02208098((void *) (arg), 9);
        return;
    }
    if (func_ov002_0220b498((void *) ((char *) arg + 0x2b3c)) != 0) {
        func_ov106_0229c458(arg);
    }
}
