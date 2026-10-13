/* func_02067d7c @ 0x02067d7c, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02067e04(unsigned char *param);
extern int func_020a80c4(int a, int b, int c, int d);
extern int func_020a7ee4(void);

int func_02067d7c(unsigned char *param)
{
    int result = 0;
    if (param[0x1e98] == 0) {
        if (func_02067e04(param) == 0) {
            if (func_020a80c4(8, 0xf8, 0x70, 0xc0) != 0) {
                result = 1;
            } else if (func_020a7ee4() != 0) {
                result = 1;
            }
        }
    }
    return result;
}
