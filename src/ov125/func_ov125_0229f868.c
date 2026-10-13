/* func_ov125_0229f868 @ 0x0229f868, 0x28 bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char func_ov125_0229f868(unsigned char *param0, unsigned char param1, unsigned char param2,
                                         unsigned char param3);

unsigned char func_ov125_0229f868(unsigned char *param0, unsigned char param1, unsigned char param2, unsigned char param3)
{
    unsigned char temp;
    unsigned char result;

    temp = param0[0x87c];
    if (temp >= param1 && temp <= param2) {
        param0[0x87c] = temp + (param3 - param1);
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
