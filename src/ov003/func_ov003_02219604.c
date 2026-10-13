/* func_ov003_02219604 @ 0x02219604, 0x44 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_02095764(unsigned short *, int);

#define IN(v, lo, hi) ((v) >= (lo) && (v) <= (hi))

int func_ov003_02219604(void)
{
    unsigned short w;
    unsigned int t;
    unsigned short wv;

    func_02095764(&w, 4);
    t = 0;
    wv = w;
    if (*(volatile unsigned short *) &w >= 0x1376 && wv <= 0x1376) {
        t = 1;
    }
    if (t > 0 || IN(wv, 0x1377, 0x1377)) {
        return 1;
    }
    return 0;
}
