/* func_ov003_0222a784 @ 0x0222a784, 0x36 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

void *func_02095794(int k);
int func_ov003_02228150(void *p, void *q);

int func_ov003_0222a784(void *p)
{
    int r = 0;
    void *h;
    if (p == 0) {
        return r;
    }
    h = func_02095794(4);
    if (h == 0) {
        return r;
    }
    if (func_ov003_02228150(p, h) != 0) {
        r = 1;
    }
    return r;
}
