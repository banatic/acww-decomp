/* func_0209adb0 @ 0x0209adb0, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209b56c(void *);
extern void func_0209ac30(void *);
extern void func_0209b23c(void *);
extern void func_0209af04(void *);

void func_0209adb0(void *arg0)
{
    int i;
    void *p;

    for (i = 0; i < 2; i++) {
        p = (char *) arg0 + i * 0x30;
        func_0209b56c(p);
    }

    func_0209ac30(arg0);
    func_0209b23c((char *) arg0 + 0x94);
    func_0209af04((char *) arg0 + 0xa4);
}
