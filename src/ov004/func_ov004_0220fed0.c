/* func_ov004_0220fed0 @ 0x0220fed0, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02099870(int object);
extern int func_02094ffc(void *object);
int func_ov004_0220fed0(void)
{
    int object;
    int child;
    if ((object = func_020984e8()) != 0 && (child = func_02099870(object)) != 0) {
        if (func_02094ffc((void *) child) == 0) {
            return 1;
        }
        return 0;
    }
    return 0;
}
