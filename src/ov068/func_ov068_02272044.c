/* func_ov068_02272044 @ 0x02272044, 0x38 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02096718(int);
extern int func_02008258(void *, int);
extern int func_ov068_02271e98(void *, int, int);

int func_ov068_02272044(void)
{
    void *p = func_02096718(4);
    if (p) {
        *(int *) ((char *) p + 0x7fc) = func_02008258(p, *(int *) ((char *) p + 0x7f0));
        return func_ov068_02271e98(p, 6, -1);
    } else {
        return 0;
    }
}
