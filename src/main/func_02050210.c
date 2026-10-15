/* func_02050210 @ 0x02050210, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209d238(void *a, void *b);
extern int func_0209d0ac(void *a, int b, int c);
extern int func_0209d088(void *a);
extern int func_02055f2c(void *a, int b, int c);
extern void func_02050394(void *a, void *b);
extern int data_020dcd84[];

int func_02050210(void *a, void *b, void *c)
{
    int success = 0;
    int off, ret1, ret2;
    char *ptr;

    if (b == 0 || c == 0) {
        return 0;
    }

    off = *(int *) ((char *) c + 0x40);
    ret1 = func_0209d238(b, (char *) c + 0x48);
    ptr = (char *) c + 0x4c;

    if (func_0209d0ac(ptr, ret1, data_020dcd84[off - 0x38])) {
        ret2 = func_0209d088(ptr);
        func_02055f2c((char *) c + 0x98, ret2, 0);
        *(int *) ((char *) c + 0x44) = 3;
        func_02050394(a, c);
        success = 1;
    }

    return success;
}
