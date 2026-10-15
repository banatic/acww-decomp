/* func_ov048_022609a4 @ 0x022609a4, 0x2a bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern int func_020ec1e8(void);

unsigned char func_ov048_022609a4(void *receiver)
{
    int flag = 1;
    if (func_020ec1e8() != 3 && func_020ec1e8() != 4) {
        flag = 0;
    }
    {
        int val = flag ? 0x80 : 0x63;
        return ((unsigned) val << 24) >> 24;
    }
}
