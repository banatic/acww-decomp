/* func_ov122_022a1e40 @ 0x022a1e40, 0x4e bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern int func_020ee45c(void *a, int b);
extern int func_0206fb9c(void);
extern void func_ov090_022993cc(int a, unsigned char b);
extern void func_0206fba8(int a);
extern void func_ov002_022080a0(void *a, int b);

int func_ov122_022a1e40(void *self, int mode)
{
    int a, b;

    a = func_020ee45c(self, mode);
    if (mode != -1 && mode != 8) {
        b = func_0206fb9c();
        func_ov090_022993cc(a, (unsigned char) mode);
        func_0206fba8(b);
        *((unsigned char *) self + 0x8c) = 2;
        func_ov002_022080a0(self, 1);
        return 1;
    } else {
        return 0;
    }
}
