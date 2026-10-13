/* func_ov003_02226ef4 @ 0x02226ef4, 0x24 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov003_02239c7c;
int func_ov003_022272c0(void *a, void *b, void *c, void *d, int e);
int func_ov003_02226ef4(void *a, void *b, void *c)
{
    int ok = 1;
    if (func_ov003_022272c0(a, b, c, &data_ov003_02239c7c, 1) == 0) {
        ok = 0;
    }
    return ok;
}
