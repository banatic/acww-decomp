/* func_0207fe94 @ 0x0207fe94, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0207fe94(int arg0, int *out1, int *out2, int mode, int step, unsigned char flag)
{
    int result = 0;
    switch (mode) {
        case 0:
            *out1 = 5;
            *out2 = 0xa;
            result = 1;
            break;
        case 1:
            *out1 = 1;
            *out2 = 5;
            if (step == 2 || (step == 8 && flag != 0)) {
                *out1 = 3;
            }
            result = 1;
            break;
        case 2:
            *out1 = 0;
            if (step == 2 || (step == 8 && flag != 0)) {
                *out2 = 3;
            } else {
                *out2 = 1;
            }
            result = 1;
            break;
    }
    return result;
}
