/* func_02099e9c @ 0x02099e9c, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020984e8(void);
extern void *func_02099734(void *a);
extern volatile unsigned short *func_02098f48(void *a, int b);
extern int func_02098e74(void *a, int i);
extern int func_0204bcdc(volatile unsigned short *p);
extern int func_0204bc64(volatile unsigned short *p);

int func_02099e9c(volatile unsigned short *key)
{
    void *ctx;
    volatile unsigned short *arr;
    int i;
    unsigned int ok;
    unsigned short va, vb;

    ctx = func_020984e8();
    arr = func_02098f48(func_02099734(ctx), 0);
    for (i = 0; i < 15; i++) {
        if (func_02098e74(func_02099734(ctx), i) == 0) {
            continue;
        }
        if (func_0204bcdc(&arr[i]) != 0) {
            ok = (func_0204bc64(&arr[i]) == func_0204bc64(key)) ? 1 : 0;
        } else {
            va = arr[i];
            vb = *key;
            ok = (va == vb) ? 1 : 0;
        }
        if (ok != 0) {
            return i;
        }
    }
    return -1;
}
