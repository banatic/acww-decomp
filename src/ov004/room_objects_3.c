/* room_objects_3: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0223c144 @ 0x0223c144, 0x9c bytes, Thumb
 * func_ov004_0223c130 @ 0x0223c130, 0x12 bytes, Thumb
 * func_ov004_0223c10c @ 0x0223c10c, 0x24 bytes, Thumb
 */

extern void *func_ov004_0223ce84(void);
extern char *func_ov004_0223cd58(void *tbl, unsigned int i);
extern int func_020644cc(int);
extern int func_020b5de0(int);
extern int func_020b65c4(void);
extern int func_020b6730(void);

int func_ov004_0223c130(void);

int func_ov004_0223c144(int key)
{
    unsigned int n = (unsigned int) func_ov004_0223c130();
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

int func_ov004_0223c130(void)
{
    // DECLS
    // ENDDECLS
    return func_020b5de0(func_020b65c4());
}

int func_ov004_0223c10c(void)
{
    int r;
    int a = func_020b65c4();
    if (func_020b6730() != 0 || a == 0xa || a == 0xf) {
        r = 1;
    } else {
        r = 0;
    }
    return r;
}
