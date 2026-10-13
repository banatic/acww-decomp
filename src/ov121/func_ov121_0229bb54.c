/* func_ov121_0229bb54 @ 0x0229bb54, 0x3a bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f3c(void *p, int n);
extern void func_020027f0(int n);
extern void func_ov002_022080a0(void *p, int n);
extern void func_ov002_02207e80(void *p, int a, int b, int c);
extern int func_ov002_02207f60(void *p);

void func_ov121_0229bb54(void *arg)
{
    if (func_ov002_02207f3c(arg, 0)) {
        func_020027f0(6);
        func_ov002_022080a0(arg, 5);
    } else {
        func_ov002_02207e80(arg, 6, 0, 0);
        *(int *) ((char *) arg + 0x94) = func_ov002_02207f60(arg);
    }
}
