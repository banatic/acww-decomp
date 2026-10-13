/* func_ov003_0221bc50 @ 0x0221bc50, 0x24 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_0221bfa8(void *arg, int val);

void func_ov003_0221bc50(void *arg)
{
    void *p = *((void **) ((char *) arg + 0x12c));
    if (p != 0) {
        if (*((int *) ((char *) p + 4)) == 0) {
            func_ov003_0221bfa8(arg, 7);
        }
    }
}
