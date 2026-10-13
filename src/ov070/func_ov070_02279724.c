/* func_ov070_02279724 @ 0x02279724, 0x34 bytes, Thumb, module ov070
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov070_02279758(int, unsigned char *, int);
extern int func_020644cc(int);

int func_ov070_02279724(int a, unsigned char *str, int len)
{
    int i;
    int result;
    unsigned char *p;

    a = func_ov070_02279758(a, str, len);
    result = 0;
    a = func_020644cc(a);

    p = str;
    for (i = 0; i < len; p++, i++) {
        if (*p == 0) {
            if (a == 0) {
                result = i;
                break;
            }
            a--;
        }
    }

    return result;
}
