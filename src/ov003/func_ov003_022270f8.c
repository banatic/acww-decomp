/* func_ov003_022270f8 @ 0x022270f8, 0x20 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void **data_ov003_02239f38[];
int func_ov003_02227170(void *self, int k);
void *func_ov003_022270f8(void *self, int i)
{
    return data_ov003_02239f38[func_ov003_02227170(self, 2)][i];
}
