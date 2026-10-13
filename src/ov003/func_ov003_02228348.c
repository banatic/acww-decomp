/* func_ov003_02228348 @ 0x02228348, 0x36 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

int func_ov003_022282e8(void *a, int k, void *b);
int func_02095794(int k);
void func_ov003_022282b8(void *b, void *q);

int func_ov003_02228348(void *a, void *b)
{
    int r = 0;
    if (func_ov003_022282e8(a, 4, b) != 0) {
        void *h = (void *) func_02095794(4);
        if (h == 0) {
            return r;
        }
        func_ov003_022282b8(b, h);
        r = 1;
    }
    return r;
}
