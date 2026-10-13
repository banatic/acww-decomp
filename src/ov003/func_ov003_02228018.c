/* func_ov003_02228018 @ 0x02228018, 0x24 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

void *func_020961a8(void *a);
int func_ov003_02228018(void *a)
{
    int r = 0;
    char *o = (char *) func_020961a8(a);
    if (o != 0) {
        if (*(int *) (o + 0x98) > 0x548) {
            r = 1;
        }
    }
    return r;
}
