/* func_ov102_0229da20 @ 0x0229da20, 0x70 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *p);
extern int func_ov102_0229d444(void *p, unsigned char b);
extern void func_ov102_0229ca58(void *p);
extern void func_ov102_0229c318(void *p);
extern void func_ov102_0229c460(void *p, int x);

void func_ov102_0229da20(unsigned char *p)
{
    if (func_0208e484(p + 0x2274) == 0) {
        return;
    }
    if (func_ov102_0229d444(p, p[0x25a5]) != 0) {
        unsigned char val = (unsigned char) (p[0x25a5] - 0x1e);
        if (val == p[0x25aa]) {
            func_ov102_0229ca58(p);
        } else {
            p[0x25aa] = val;
            func_ov102_0229c318(p);
        }
    } else {
        if (p[0x25a5] == 0x24) {
            func_ov102_0229c460(p, 1);
        } else {
            func_ov102_0229ca58(p);
        }
    }
}
