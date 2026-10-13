/* func_ov121_02299aac @ 0x02299aac, 0x2c bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern int func_02095f4c(void);
extern int func_02095f58(void);

int func_ov121_02299aac(int param1, int param2)
{
    int result;

    if (param2 == 2) {
        if (func_02095f4c() == 0) {
            result = 1;
        } else {
            result = 0;
        }
    } else {
        if (func_02095f58() == 0) {
            result = 1;
        } else {
            result = 0;
        }
    }

    return result;
}
