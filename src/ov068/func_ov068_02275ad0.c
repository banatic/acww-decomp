/* func_ov068_02275ad0 @ 0x02275ad0, 0x4c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov068_022763e4(void);
extern void *func_020961a8(int);
extern int func_020ea990(void *, void *);
extern void func_0203e0a8(void *, int);

void func_ov068_02275ad0(void *param)
{
    void *p;
    int result;
    int i;
    int *q;
    int local[4];

    if (func_ov068_022763e4()) {
        p = func_020961a8(4);
        if (p) {
            q = (int *) ((char *) p + 0x5c);
            local[0] = *(int *) ((char *) p + 0x5c);
            local[1] = q[1];
            local[2] = q[2];
            result = func_020ea990(local, (char *) param + 0x5c);
            if (result > 0x4e66) {
                func_0203e0a8(param, 0);
            }
        }
    }
}
