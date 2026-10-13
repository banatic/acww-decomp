/* func_ov003_022196e0 @ 0x022196e0, 0x38 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02096718(void *);
extern int func_0200fbe0(void *);
extern void *func_02095794(void *);

typedef struct {
    int a;
    int b;
} Pair2;

void *func_ov003_022196e0(void *arg)
{
    void *p = func_02096718(arg);
    if (p != 0 && func_0200fbe0(p) == 3) {
        Pair2 *base = (Pair2 *) ((char *) p + 0x5c8);
        if (base->b > 1) {
            return base + 1;
        }
    }
    return func_02095794(arg);
}
