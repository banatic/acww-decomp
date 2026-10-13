/* func_ov109_0229cae0 @ 0x0229cae0, 0x2e bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov109_0229ccb4(void *a0, void *a1);
extern int func_ov109_0229cc98(void *a0, void *a1);
extern int func_ov094_0229a8bc(char *ptr, int value);

int func_ov109_0229cae0(void *a0, void *a1)
{
    if (func_ov109_0229ccb4(a0, a1)) {
        int value = func_ov109_0229cc98(a0, a1);
        return func_ov094_0229a8bc((char *) a0 + 0xcc, value);
    }
    return 0;
}
