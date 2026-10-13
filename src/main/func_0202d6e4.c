/* func_0202d6e4 @ 0x0202d6e4, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int);

int func_0202d6e4(unsigned char *data, int len)
{
    unsigned char sum = 0;
    int result = -1;
    int i;
    unsigned char target;
    unsigned char acc;
    int j;

    for (i = 0; i < len; i++) {
        sum += data[i];
    }

    if (sum != 0) {
        target = (unsigned char) func_020644cc(sum);

        acc = 0;

        for (j = 0; j < len; j++) {
            acc += data[j];

            if (target < acc) {
                result = j;
                break;
            }
        }
    }

    return result;
}
