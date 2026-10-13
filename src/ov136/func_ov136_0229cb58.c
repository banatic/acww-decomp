/* func_ov136_0229cb58 @ 0x0229cb58, 0x48 bytes, Thumb, module ov136
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov134_02299a60(void *);
extern void func_ov002_02208098(void *, int);
extern void func_ov136_0229c628(void *);
extern int func_ov136_0229c794(void *);
extern int func_ov136_0229c750(void *);
extern void func_ov002_0220a0b4(void *, int, int);

void func_ov136_0229cb58(void *arg)
{
    int a;
    int b;

    if (func_ov134_02299a60((char *) arg + 0x2c4)) {
        func_ov002_02208098(arg, 7);
        func_ov136_0229c628(arg);
    }

    a = func_ov136_0229c794(arg);
    b = func_ov136_0229c750(arg);
    arg = (char *) arg + 0x94;
    func_ov002_0220a0b4(arg, a, b);
}
