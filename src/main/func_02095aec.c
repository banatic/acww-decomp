/* func_02095aec @ 0x02095aec, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02096718(int);
extern int func_02008750(int, void *, int, int);

int func_02095aec(unsigned short *param)
{
    int r;
    r = func_02096718(4);
    if (r != 0) {
        unsigned short tmp;
        tmp = *param;
        return func_02008750(r, &tmp, 6, -1);
    } else {
        return 0;
    }
}
