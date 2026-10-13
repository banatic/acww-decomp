/* func_ov004_0220fe24 @ 0x0220fe24, 0x86 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020961a8(int i);
extern int func_ov004_0220feac(void *self, int a, void *p, int b);
extern unsigned int func_020826cc(void);
extern void *func_02082664(unsigned int i);

int func_ov004_0220fe24(void *self, int a1, int a2, int a3, int a4)
{
    void *base;
    void *o;
    unsigned int i;
    unsigned int j;
    unsigned int n;

    base = func_020961a8(4);
    if (base != 0) {
        for (i = 0; i < 4; i++) {
            o = func_020961a8(i);
            if (o != 0 && base != o && func_ov004_0220feac(self, a1, (char *) o + 0x5c, a3) != 0) {
                return 0;
            }
        }
        n = func_020826cc();
        for (j = 0; j < n; j++) {
            o = func_02082664(j);
            if (o != 0 && func_ov004_0220feac(self, a2, (char *) o + 0x5c, a4) != 0) {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}
