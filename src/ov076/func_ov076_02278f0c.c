/* func_ov076_02278f0c @ 0x02278f0c, 0x50 bytes, Thumb, module ov076
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204bcdc(unsigned short *p);
extern int func_0204bc64(unsigned short *p);

int func_ov076_02278f0c(unsigned short *p, int flag)
{
    if (flag == 0) {
        if (func_0204bcdc(p) != 0) {
            unsigned short local = 0x1559;
            if (func_0204bc64(p) == func_0204bc64(&local)) {
                return 1;
            } else {
                return 0;
            }
        } else {
            if (*p == 0x1559) {
                return 1;
            } else {
                return 0;
            }
        }
    }
    return 0;
}
