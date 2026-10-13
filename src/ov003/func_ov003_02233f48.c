/* func_ov003_02233f48 @ 0x02233f48, 0xe8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_020961a8(int id);
extern int func_020ea990(int *a, int *b);

void func_ov003_02233f48(char *self, int *out, int *pv, u8 *pflag, u8 a5, u8 a6)
{
    void *o;
    short v;
    int lim;
    int w;
    int *s;
    int d;

    o = func_020961a8(a5);
    if (o != 0) {
        v = *(u8 *) (self + 0x254);
        lim = *(int *) (self + 0x224);
        w = *(int *) ((char *) o + 0x98);
        s = (int *) ((char *) o + 0x5c);
        out[0] = s[0];
        out[1] = s[1];
        out[2] = s[2];
        *pv = func_020ea990(out, (int *) (self + 0x204));
        if (a6 != 0) {
            *pflag = 0;
            d = *pv;
            if (d < 0x2000) {
                v = v + 0x19;
            } else if (d > lim || w == 0) {
                *pflag = 1;
            } else if (w <= 0x3e8) {
                v = v + 1;
            } else if (w <= 0x44c) {
                v = v + 3;
            } else if (w <= 0x490) {
                v = v + 5;
            } else if (w == 0x491) {
                v = v + 8;
            } else {
                v = v + 0xf;
            }
            if (v > 0xfe) {
                v = 0xfe;
            }
            *(u8 *) (self + 0x254) = (u8) v;
        }
    }
}
