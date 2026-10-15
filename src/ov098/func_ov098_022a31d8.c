/* func_ov098_022a31d8 @ 0x022a31d8, 0x50 bytes, Thumb, module ov098
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02099020(int, int);
extern int func_ov094_022999e4(unsigned int);

int func_ov098_022a31d8(void *a, unsigned int v)
{
    volatile long long unused;
    (void) &unused;
    if (func_02099020(func_020984e8(), 1) != 0) {
        if ((v >= 0x14fe && v <= 0x1517) || (v >= 0x151d && v <= 0x151e)) {
            return 0;
        }
    }
    return func_ov094_022999e4(v);
}
