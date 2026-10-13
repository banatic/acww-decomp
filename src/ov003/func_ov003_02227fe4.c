/* func_ov003_02227fe4 @ 0x02227fe4, 0x34 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

void *func_020961a8(void *a);
long long func_020ea940(void *p, void *q);

int func_ov003_02227fe4(void *a, void *b, void *c)
{
    char *o = (char *) func_020961a8(c);
    if (o == 0) {
        return 0;
    }
    if (func_020ea940(o + 0x5c, b) <= 0x135c3) {
        return 1;
    }
    return 0;
}
