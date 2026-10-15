/* func_ov048_022609d0 @ 0x022609d0, 0x2a bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern int func_020ec1e8(void);

unsigned char func_ov048_022609d0(void *receiver)
{
    int flag = 1;
    if (func_020ec1e8() != 3 && func_020ec1e8() != 4) {
        flag = 0;
    }
    return (unsigned char) (flag ? 0x82 : 0x65);
}
