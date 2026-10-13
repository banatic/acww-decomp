/* func_0207d578 @ 0x0207d578, 0x42 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(int a);
extern int func_02003704(int x);
extern void func_0209e474(void *p);
extern int func_020036e8(int x);
extern int func_020821d4(int x, void *p);

int func_0207d578(int a, void *b)
{
    int work[2];

    if (func_02003704(func_0208150c(a)) == 0) {
        goto fail;
    }

    work[0] = 0;
    work[1] = 0;

    if (b == 0) {
        func_0209e474(work);
        b = work;
    }

    return func_020821d4(func_020036e8(func_0208150c(a)), b);

fail:
    return 0;
}
