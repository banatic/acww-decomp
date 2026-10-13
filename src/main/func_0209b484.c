/* func_0209b484 @ 0x0209b484, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern int func_02073d90(int);
extern int func_0209c310(int);

int func_0209b484(int a, int b)
{
    int r, result;

    if (func_02073d90(data_020ccf94)) {
        return 0;
    }

    r = func_0209c310(b);
    result = 0;

    switch (a) {
        case 10:
            if (r == 1) {
                result = 1;
            }
            break;
        case 19:
            if (r == 1) {
                result = 1;
            }
            // fall through
        default:
            break;
    }

    return result;
}
