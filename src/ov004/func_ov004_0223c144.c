/* func_ov004_0223c144 @ 0x0223c144, 0x9c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_ov004_0223c130(void);
extern void *func_ov004_0223ce84(void);
extern char *func_ov004_0223cd58(void *tbl, unsigned int i);
extern int func_020644cc(int);

int func_ov004_0223c144(int key)
{
    unsigned int n = func_ov004_0223c130();
    void *tbl = func_ov004_0223ce84();
    int cnt = 0;
    unsigned int i = 0;
    int zero = 0;
    int pick;
    int k;
    int zero2;
    char *e;
    int a;
    for (; i < n; i++) {
        e = func_ov004_0223cd58(tbl, i);
        if (e != 0) {
            a = *(int *) (e + 0x778);
            if (a != ~zero && key == *(int *) (e + 0x774)) {
                cnt++;
            }
        }
    }
    if (cnt != 0) {
        pick = func_020644cc(cnt);
        k = 0;
        i = 0;
        zero2 = 0;
        for (; i < n; i++) {
            e = func_ov004_0223cd58(tbl, i);
            if (e != 0) {
                a = *(int *) (e + 0x778);
                if (a != ~zero2 && key == *(int *) (e + 0x774)) {
                    if (k == pick) {
                        return a;
                    }
                    k++;
                }
            }
        }
    }
    return ~0;
}
