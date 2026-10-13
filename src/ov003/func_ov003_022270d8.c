/* func_ov003_022270d8 @ 0x022270d8, 0x20 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void **data_ov003_02239ee4[];
int func_ov003_02227170(void *self, int k);
void *func_ov003_022270d8(void *self, int i)
{
    return data_ov003_02239ee4[func_ov003_02227170(self, 2)][i];
}
