/* func_ov122_022a1e40 @ 0x022a1e40, 0x4e bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern int func_020ee45c(void *a);
extern int func_0206fb9c(void);
extern void func_ov090_022993cc(int a, unsigned char b);
extern void func_0206fba8(int a);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);

int func_ov122_022a1e40(void *self, int mode)
{
    int a, b;

    a = func_020ee45c(self);
    if (mode != -1 && mode != 8) {
        b = func_0206fb9c();
        func_ov090_022993cc(a, (unsigned char) mode);
        func_0206fba8(b);
        *((unsigned char *) self + 0x8c) = 2;
        func_ov002_022080a0((void *) (self), 1);
        return 1;
    } else {
        return 0;
    }
}
