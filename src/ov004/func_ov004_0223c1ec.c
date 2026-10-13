/* func_ov004_0223c1ec @ 0x0223c1ec, 0x78 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef int (*Pred)(void *);
extern void *func_ov004_0223ce84(void);
extern char *func_ov004_0223cd58(void *, unsigned int);
extern int func_ov004_0220d2b8(void *);
extern unsigned int func_ov004_0223c130(void);
extern int func_ov004_0223c264(Pred);
extern int func_020644cc(int);
extern void func_ov004_0220d280(void *, int, int);

char *func_ov004_0223c1ec(Pred pred, int v)
{
    int cnt = func_ov004_0223c264(pred);
    if (cnt != 0) {
        int pick = func_020644cc(cnt);
        int n = 0;
        unsigned int i;
        for (i = 0; i < func_ov004_0223c130(); i++) {
            char *o = func_ov004_0223cd58(func_ov004_0223ce84(), i);
            if (o != 0) {
                if (pred == 0 || (pred != 0 && pred(o) != 0)) {
                    if (func_ov004_0220d2b8(o + 0x740) != 0) {
                        if (n == pick) {
                            func_ov004_0220d280(o + 0x740, 0, v);
                            return o;
                        }
                        n++;
                    }
                }
            }
        }
    }
    return 0;
}
