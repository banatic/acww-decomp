/* func_0207bfa4 @ 0x0207bfa4, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207c048(char *);
extern int func_0207bfdc(char *);
extern int func_0207dc30(char *, int);

int func_0207bfa4(char *a, int b)
{
    int result;
    result = func_0207c048(a);
    if (result != 0) {
        result = func_0207bfdc(a);
        if (result != -1) {
            return func_0207dc30(a + result * 0x7EC, b);
        }
    }
    return result;
}
