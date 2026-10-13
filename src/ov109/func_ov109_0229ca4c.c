/* func_ov109_0229ca4c @ 0x0229ca4c, 0x2e bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov109_0229ccb4(void *a, int b);
extern int func_ov109_0229cc98(void *a, int b);
extern int func_ov094_0229aa84(void *a, int b);

int func_ov109_0229ca4c(void *a, int b)
{
    if (func_ov109_0229ccb4(a, b) != 0) {
        return func_ov094_0229aa84((char *) a + 0xcc, func_ov109_0229cc98(a, b));
    } else {
        return 0xf1;
    }
}
