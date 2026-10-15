/* func_020b060c @ 0x020b060c, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b0a20(char *p);
extern void func_020b0970(char *p, int b, int c, int d);

int func_020b060c(char *a, int b, int c, int d)
{
    unsigned int i;
    char *p;

    for (i = 0; i < 3; i++) {
        p = a + i * 6;
        if (func_020b0a20(p) == 0) {
            func_020b0970(p, b, c, d);
            return i;
        }
    }
    return -1;
}
