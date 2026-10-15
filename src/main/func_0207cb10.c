/* func_0207cb10 @ 0x0207cb10, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020951bc(void *);
extern int func_0208150c(void *);
extern int func_02003704(int);
extern int func_020807a8(void *, void *);
extern int func_02081d20(signed char *);
extern int func_020644cc(int);
extern void *func_0207cc94(void *, int, int);

void *func_0207cb10(void *p0, void *p1)
{
    signed char *tested_value0;
    int i;
    void *best = 0;

    if (func_020951bc(p1) != 0) {
        void *p = p0;
        int bestVal = -128;
        for (i = 0; i < 8; i++) {
            if (func_02003704(func_0208150c(p)) != 0) {
                if ((tested_value0 = (signed char *) (func_020807a8(p, p1))) != 0) {
                    int val = func_02081d20(tested_value0);
                    if (best == 0) {
                        best = p;
                        bestVal = val;
                    } else {
                        if (val > bestVal) {
                            best = p;
                            bestVal = val;
                        } else if (val == bestVal) {
                            if (func_020644cc(10) & 1) {
                                best = p;
                            }
                        }
                    }
                }
            }
            p = (char *) p + 0x7ec;
        }
    }

    if (best == 0) {
        best = func_0207cc94(p0, 0, 0);
    }
    return best;
}
