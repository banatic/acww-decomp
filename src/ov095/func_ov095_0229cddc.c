/* func_ov095_0229cddc @ 0x0229cddc, 0x14 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov095_0229cdf0(void *a, int b);

int func_ov095_0229cddc(void *a, int b)
{
    if (b == -1) {
        b = *(int *) ((char *) a + 0x28);
    }
    return func_ov095_0229cdf0(a, b);
}
