/* func_ov003_02226f5c @ 0x02226f5c, 0x44 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov003_02239f80;
extern int data_ov003_02239f08;
int func_ov003_022272c0(void *a, void *b, void *c, void *d, int e);

int func_ov003_02226f5c(void *a, void *b, void *c, void *d, void *e)
{
    if (func_ov003_022272c0(a, b, c, &data_ov003_02239f80, 3) == 0) {
        return 0;
    }
    return func_ov003_022272c0(a, d, e, &data_ov003_02239f08, 3) != 0 ? 1 : 0;
}
