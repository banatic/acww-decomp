/* func_0209b920 @ 0x0209b920, 0x76 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209b91c(void *);
extern int func_0209bd44(int);
extern int func_0209bd04(int);
extern int func_0209bc40(int);
extern int func_0209b8d0(int);
extern int func_0209b914(int);
extern int func_0209b64c(int);
extern void func_0209ba7c(int);
extern void func_0209b90c(int, int);

void func_0209b920(int arg)
{
    int f;
    int limit;
    int idx;
    unsigned int cond;

    f = func_0209b91c((void *) arg);
    if (func_0209bd44(f) == 0) {
        return;
    }
    if (func_0209bd04(f) != 0) {
        return;
    }
    limit = func_0209b8d0((int) func_0209bc40(f));
    idx = func_0209b914(arg);
    if (idx >= limit - 1) {
        return;
    }
    if (func_0209bc40(f) == 4) {
        f = func_0209b64c(arg);
    } else {
        f = 1;
    }
    func_0209ba7c(arg);
    if (f != 0) {
        cond = 1;
    } else {
        cond = 0;
    }
    if (cond != 0) {
        func_0209b90c(arg, (unsigned char) (idx + 1));
    }
}
