/* func_ov003_02227154 @ 0x02227154, 0x1c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void **data_ov003_02239f20[];
int func_ov003_02227170(void *self, int k);
void *func_ov003_02227154(void *self, int k, int i)
{
    return data_ov003_02239f20[func_ov003_02227170(self, k)][i];
}
