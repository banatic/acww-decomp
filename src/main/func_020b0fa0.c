/* func_020b0fa0 @ 0x020b0fa0, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020b1498(int);
extern void func_020b0fc8(void *, void *, int);

void func_020b0fa0(void *arg)
{
    int i;
    void *p;

    for (i = 0; i < 16; i++) {
        p = func_020b1498(i);
        if (p != 0) {
            func_020b0fc8(arg, p, 7);
        }
    }
}
