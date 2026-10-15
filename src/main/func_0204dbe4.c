/* func_0204dbe4 @ 0x0204dbe4, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021e5a2c;
extern void *func_0207cec0(void *arg, int);
extern int func_0207ffdc(void *arg, int *a, int *b);
extern int func_0204d7f8(void *a, int v1, int v2, void *c);
extern void func_0207f4c8(void *res, void *a);

int func_0204dbe4(void *a, void *b, void *c)
{
    int v1 = 2;
    void *ptr;
    int v2 = 0;
    int ret = 0;

    ptr = func_0207cec0(&data_021e5a2c, (int) b);
    if (ptr != 0) {
        func_0207ffdc(ptr, &v1, &v2);
    }
    if (ptr != 0) {
        if (func_0204d7f8(a, v1, v2, c) != 0) {
            func_0207f4c8(ptr, a);
            ret = 1;
        }
    }
    return ret;
}
