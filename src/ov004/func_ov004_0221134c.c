/* func_ov004_0221134c @ 0x0221134c, 0x2e bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0220fde0(void *self);
extern int func_02053818(int);
extern int func_ov004_0220e5c8(void *self);
int func_ov004_0221134c(void *self)
{
    if (self != 0) {
        if (func_02053818((int) func_ov004_0220fde0(self)) != 0) {
            if (func_ov004_0220e5c8(self) == 0) {
                return 1;
            }
        }
        return 0;
    }
    return 0;
}
