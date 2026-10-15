/* func_020b1394 @ 0x020b1394, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b15b0(void);
extern int func_020b1974(int a, int b);
extern char *func_020b1530(int a);
extern void *func_020b18fc(char *a);
extern void func_020a8874(char *dst, const char *src, int len);
extern int func_020a8a70(int a, char *b, int c, int d);
extern void *func_020b18e4(char *a);

int func_020b1394(int a0, int a1)
{
    char buf[0x1c];
    char *p;

    if (func_020b1974(func_020b15b0(), a1) == 0) {
        return 0;
    }

    p = func_020b1530(a1);
    func_020b18fc(buf);
    func_020a8874(buf, p + 0x1e, 6);
    func_020a8a70(a0, buf, 0, 0);
    func_020b18e4(buf);

    return 1;
}
