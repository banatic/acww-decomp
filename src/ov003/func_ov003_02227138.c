/* func_ov003_02227138 @ 0x02227138, 0x1c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void **data_ov003_02239f8c[];
int func_ov003_02227170(void *self, int k);
void *func_ov003_02227138(void *self, int k, int i)
{
    return data_ov003_02239f8c[func_ov003_02227170(self, k)][i];
}
