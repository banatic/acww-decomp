/* func_020975c4 @ 0x020975c4, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021f37f4;
extern int func_02090000(int *);
extern int func_02097ad0(int);
extern void *func_0208ffe4(int *);
extern void *func_020984e8(void);
extern void *func_0209985c(void *);
extern void func_02066560(void *, void *);
extern void func_02066478(void *);
extern int func_02097a74(void *, void *, int);
extern void func_02090018(int *);

void func_020975c4(void)
{
    int *base = &data_021f37f4;
    void *p;
    void *q;

    if (func_02090000(base) == 0) {
        return;
    }
    if (func_02097ad0(-1) != 0) {
        return;
    }
    p = func_0208ffe4(base);
    q = func_0209985c(func_020984e8());
    func_02066560(p, q);
    func_02066478(p);
    if (func_02097a74(p, q, 0) == 0) {
        return;
    }
    func_02090018(base);
}
