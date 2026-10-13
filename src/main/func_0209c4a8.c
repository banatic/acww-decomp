/* func_0209c4a8 @ 0x0209c4a8, 0x72 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int);

int func_0209c4a8(const unsigned char *data)
{
    unsigned char result = 8;
    unsigned short mask = 0;
    int prev = -1;
    int count = 0;
    int i, j;
    int rnd;

    for (i = 0; i < 8; i++) {
        unsigned char c = data[i];
        if (c > prev) {
            prev = c;
            mask = (1 << i);
            count = 1;
        } else if (prev == c) {
            mask |= (1 << i);
            count++;
        }
    }

    if (count > 0) {
        rnd = func_020644cc(count);
        for (j = 0; j < 8; j++) {
            if ((mask >> j) & 1) {
                if (rnd == 0) {
                    result = (unsigned char) j;
                    break;
                }
                rnd--;
            }
        }
    }
    return result;
}
