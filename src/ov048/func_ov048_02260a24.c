/* func_ov048_02260a24 @ 0x02260a24, 0x3c bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern int func_02073918(int, int);
extern int func_02073d90(int);
extern int func_020ec1e8(void);

int func_ov048_02260a24(void *receiver)
{
    int r4;

    r4 = data_020ccf94;
    if (func_02073918(r4, 0) != 0) {
        if (func_02073d90(r4) != 0) {
            return 0x17;
        } else {
            if (func_020ec1e8() == 3) {
                return 0x3a;
            } else {
                return 0x38;
            }
        }
    } else {
        return 0x3d;
    }
}
