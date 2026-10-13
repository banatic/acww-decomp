/* func_0201111c @ 0x0201111c, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02011368(void);
extern int func_0209975c(int);

int func_0201111c(void)
{
    int v = func_02011368();
    if (v) {
        return func_0209975c(v);
    } else {
        return 0;
    }
}
