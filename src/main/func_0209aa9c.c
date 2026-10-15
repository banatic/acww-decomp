/* func_0209aa9c @ 0x0209aa9c, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209ad9c(int a, int b);
extern int func_0209b4d4(void *);
extern int func_0209bc40(int a);
extern int func_0209bba0(int a);
extern void func_0209bb90(int a, int b);

void func_0209aa9c(int arg0)
{
    int val;
    val = (func_0209b4d4((void *) func_0209ad9c(arg0, 0)));
    if (func_0209bc40(val) == 15) {
        if (func_0209bba0(val) == 0) {
            func_0209bb90(val, 1);
        }
    }
}
