/* func_ov094_0229ad20 @ 0x0229ad20, 0x42 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020984e8(void);
extern void *func_02099734(void *);
extern short *func_02098f48(void *, int);
extern int func_02098e8c(void *, int);
extern void func_ov094_0229ad64(void *, int, short *, int);

void func_ov094_0229ad20(void *p)
{
    void *x;
    short *base;
    int i, j;

    x = func_02099734(func_020984e8());
    base = func_02098f48(x, 0);
    for (j = 0, i = 0; i < 15; j++, i++) {
        func_ov094_0229ad64(p, j, base + i, func_02098e8c(x, i));
    }
}
