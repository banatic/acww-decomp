/* func_ov068_02272530 @ 0x02272530, 0x1c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int DWCi_GsMalloc(int param);
extern void func_ov068_02272a7c(void *param, int value);

void func_ov068_02272530(void *param)
{
    if (DWCi_GsMalloc(4) == 0) {
        func_ov068_02272a7c(param, 8);
    }
}
