/* func_ov070_0227944c @ 0x0227944c, 0xec bytes, Thumb, module ov070
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int);

unsigned char func_ov070_0227944c(int unused, int r1, int r2)
{
    unsigned char result = 0;

    switch (r2) {
        case 0:
            if (r1 == 0) {
                result = (unsigned char) (func_020644cc(3) + 1);
            } else if (r1 < 200) {
                result = (unsigned char) (func_020644cc(3) + 3);
            } else if (r1 < 1000) {
                result = (unsigned char) (func_020644cc(3) + 5);
            } else {
                result = (unsigned char) (func_020644cc(4) + 7);
            }
            break;

        case 1:
            if (r1 == 0) {
                result = (unsigned char) (func_020644cc(3) + 1);
            } else if (r1 < 160) {
                result = (unsigned char) (func_020644cc(3) + 3);
            } else if (r1 < 600) {
                result = (unsigned char) (func_020644cc(3) + 5);
            } else {
                result = (unsigned char) (func_020644cc(4) + 7);
            }
            break;

        case 2:
            if (r1 < 350) {
                result = (unsigned char) (func_020644cc(3) + 1);
            } else if (r1 < 400) {
                result = (unsigned char) (func_020644cc(3) + 4);
            } else {
                result = (unsigned char) (func_020644cc(4) + 7);
            }
            break;

        default:
            break;
    }

    return result;
}
