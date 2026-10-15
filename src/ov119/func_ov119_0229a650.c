/* func_ov119_0229a650 @ 0x0229a650, 0x4a bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov119_0229ae50(void *receiver);
extern int func_02077c3c(const char *);
extern int func_02077e50(int);

int func_ov119_0229a650(void *a, int limit)
{
    char *base;
    int count;
    int i;

    base = (char *) func_ov119_0229ae50((void *) a);
    count = 0;
    i = count;
    for (; i < 0x20; i++) {
        if (func_02077e50(func_02077c3c(base + i * 0x24))) {
            count++;
            if (i >= limit) {
                i = 0x20;
            }
        }
    }
    if (count > 0) {
        return ((count - 1) * 0x200000u) >> 24;
    } else {
        return 0;
    }
}
