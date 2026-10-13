/* func_020a1774 @ 0x020a1774, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209fb70(void *);
extern int func_020a1738(void *, void *);
extern void func_0209fb6c(void *);

int func_020a1774(void *param)
{
    void *sp;
    int result;

    func_0209fb70(&sp);
    result = func_020a1738(param, &sp);
    if (result != 0) {
        func_0209fb6c(&sp);
        return 1;
    } else {
        func_0209fb6c(&sp);
        return 0;
    }
}
