/* func_0208249c @ 0x0208249c, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0200363c(int x);
extern void func_020b4a20(void *dst, void *src, const void *fmt);
extern const char data_020e19c8[];

int func_0208249c(char *arg0, int arg1)
{
    int result = 0;
    char local;

    if (func_0200363c(arg1)) {
        local = (char) arg1;
        func_020b4a20(arg0, &local, data_020e19c8);
        result = 1;
    }

    return result;
}
