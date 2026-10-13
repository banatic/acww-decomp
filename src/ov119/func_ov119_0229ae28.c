/* func_ov119_0229ae28 @ 0x0229ae28, 0x28 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov119_0229ae50(int x);
extern int func_ov119_0229ae10(int x);

void *func_ov119_0229ae28(int x)
{
    void *base;
    int idx;
    base = func_ov119_0229ae50(x);
    idx = func_ov119_0229ae10(x);
    if (idx >= 32) {
        return 0;
    } else {
        return (void *) ((char *) base + idx * 36);
    }
}
