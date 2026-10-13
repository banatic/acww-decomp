/* func_ov068_02272cb0 @ 0x02272cb0, 0x24 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_020912d4(int, void *, int, int);

void func_ov068_02272cb0(char *base)
{
    int ret = func_020912d4(0x41, base + 0x2cc, 0, 0);
    *(int *) (base + 0x2e0) = ret;
}
