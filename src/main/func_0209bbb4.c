/* func_0209bbb4 @ 0x0209bbb4, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209bc94(unsigned int param);

int func_0209bbb4(unsigned int param)
{
    int result = 4;
    if (func_0209bc94(param) == 1) {
        if (param < 19) {
            if (param < 11) {
                result = 0;
            } else {
                result = 1;
            }
        } else {
            if (param < 20) {
                result = 2;
            } else if (param < 21) {
                result = 3;
            }
        }
    }
    return result;
}
