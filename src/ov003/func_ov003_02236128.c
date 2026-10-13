/* func_ov003_02236128 @ 0x02236128, 0x3c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *data_ov003_02262b38[8];
extern int func_ov003_0221a8d4(void *p);

void *func_ov003_02236128(void *self)
{
    unsigned int i;
    void *p;
    for (i = 0; i < 8; i++) {
        p = data_ov003_02262b38[i];
        if (p == 0) {
            continue;
        }
        if (p == self) {
            continue;
        }
        if (func_ov003_0221a8d4(p) == 0) {
            continue;
        }
        return p;
    }
    return 0;
}
