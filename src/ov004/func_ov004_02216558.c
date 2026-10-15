/* func_ov004_02216558 @ 0x02216558, 0x3e bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b67d4(void);
extern int func_ov004_0220fed0(void);
extern int func_ov004_022164a0(void *self, int k);
void func_ov004_02216558(void *self, int k)
{
    switch (k) {
        case 1:
            if (func_020b67d4() != 0 && func_ov004_0220fed0() != 0) {
                func_ov004_022164a0(self, 1);
            } else {
                func_ov004_022164a0(self, 3);
            }
            break;
        case 8:
            func_ov004_022164a0(self, 0);
            break;
    }
}
