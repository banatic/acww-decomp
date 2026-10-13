/* func_0208a038 @ 0x0208a038, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020e8ed8(int a, int b);
extern int func_020e8b4c(int a, int b);

int func_0208a038(unsigned char *p, int q)
{
    if (p[0x3c] != 0) {
        int a = *(int *) (p + 0x10);
        int b = *(int *) (p + 0x18);
        int c = func_020e8ed8(a, b);
        int d = func_020e8b4c(c, (short) (q + 0x8000));
        if (d > 0x2000) {
            return 0;
        } else {
            return 1;
        }
    }
    return 0;
}
