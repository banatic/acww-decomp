/* func_02010718 @ 0x02010718, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0200dc8c(char *p);
extern int FX_MulFunc(int a, int b);
extern int func_02089cc0(char *p, int n);
extern int func_0208a038(char *p, short s);

int func_02010718(char *p)
{
    int v;
    v = FX_MulFunc(func_0200dc8c(p), 0x6e2);
    if (v > 0x6e2) {
        v = 0x6e2;
    } else if (v < 0x108) {
        v = 0;
    }
    if (func_02089cc0(p + 0x174, 8) != 0 && func_0208a038(p + 0x174, *(short *) (p + 0x8e)) != 0) {
        if (v > 0x245) {
            v = 0x245;
        }
    } else {
        if ((*(int *) (p + 0x7a8) & 8) != 0) {
            if (v > 0x307) {
                v = 0x307;
            }
        }
    }
    return v;
}
