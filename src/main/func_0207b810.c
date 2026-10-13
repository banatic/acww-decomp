/* func_0207b810 @ 0x0207b810, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0207f270(void *key);
extern void *func_020984e8(void);
extern unsigned int func_0207b86c(void *a, void *key, void *data);
extern void *func_020794d0(void *p);
extern int func_0209bd44(void *x);
extern int func_0209bc40(void *x);

int func_0207b810(void *a, void *key, void *data)
{
    void *p;
    int result;
    unsigned int r;

    p = func_0207f270(key);
    result = 22;
    if (data == 0) {
        data = func_020984e8();
    }
    if (p != 0 && data != 0) {
        r = func_0207b86c(a, key, data);
        if (r < 22) {
            result = r;
        } else {
            if (func_0209bd44(func_020794d0(p)) != 0) {
                result = func_0209bc40(func_020794d0(p));
            }
        }
    }
    return result;
}
