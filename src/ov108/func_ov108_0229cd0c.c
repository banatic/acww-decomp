/* func_ov108_0229cd0c @ 0x0229cd0c, 0x40 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

static int func_ov094_0229bba4(char *, int unused1, int unused2);
static int func_ov094_0229b30c(char *, int);
extern int func_ov108_0229cd4c(char *, int);

int func_ov108_0229cd0c(char *a, int b, int c, int d)
{
    int x;
    x = func_ov094_0229bba4(a + 0xd50, b, c);
    if (x != 0x37) {
        if (d != 0) {
            if (func_ov094_0229b30c(a + 0xd50, x) != 0) {
                return 0x16;
            }
        }
        return func_ov108_0229cd4c(a, x);
    } else {
        return 0x16;
    }
}
