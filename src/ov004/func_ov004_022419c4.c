/* func_ov004_022419c4 @ 0x022419c4, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern char *func_020961a8(int);
extern int func_020ea990(void *, void *);

int func_ov004_022419c4(char *self)
{
    char *h = func_020961a8(4);
    if (h != 0) {
        if (func_020ea990(h + 0x5c, self + 0x2c8) < 0x4800) {
            return 1;
        }
    }
    return 0;
}
