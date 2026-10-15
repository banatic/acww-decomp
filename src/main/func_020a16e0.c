/* func_020a16e0 @ 0x020a16e0, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209fb70(int *);
extern int func_020a1738(int, int *);
extern int func_0209faf4(int *);
extern void func_0209fb6c(int *);

int func_020a16e0(void)
{
    int a, b;
    func_0209fb70(&a);
    func_020a1738(0, &a);
    func_0209fb70(&b);
    func_020a1738(1, &b);
    if (func_0209faf4(&a) == func_0209faf4(&b)) {
        func_0209fb6c(&b);
        func_0209fb6c(&a);
        return 1;
    } else {
        func_0209fb6c(&b);
        func_0209fb6c(&a);
        return 0;
    }
}
