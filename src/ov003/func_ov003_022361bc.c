/* func_ov003_022361bc @ 0x022361bc, 0x48 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *data_ov003_02262b38[8];
extern int func_ov003_0221a8e8(void *slot, void *a, int b, int c, int d, int e);

int func_ov003_022361bc(void *a, int b, int c, int d, int e)
{
    unsigned int i;
    for (i = 0; i < 8; i++) {
        if (data_ov003_02262b38[i] != 0) {
            if (func_ov003_0221a8e8(data_ov003_02262b38[i], a, b, c, d, e)) {
                return 1;
            }
        }
    }
    return 0;
}
