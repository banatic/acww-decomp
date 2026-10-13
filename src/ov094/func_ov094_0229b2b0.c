/* func_ov094_0229b2b0 @ 0x0229b2b0, 0x5c bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void *);
extern int func_02099734(int);
extern int func_02098e44(int, int);
extern int func_ov094_0229b1e8(void *, int);
extern void func_ov094_0229b154(void *, int);
extern void func_ov094_0229b134(void *, int);

void func_ov094_0229b2b0(void *self)
{
    int v = func_02098e44(func_02099734(func_020984e8(self)), 0);
    int idx = 0;
    int i = 0;
    int zero = 0;
    do {
        if (func_ov094_0229b1e8(self, v) != ~zero) {
            func_ov094_0229b154((char *) self + 8, idx);
        } else {
            func_ov094_0229b134((char *) self + 8, idx);
        }
        v += 0x100;
        idx++;
        i++;
    } while (i < 10);
}
