/* func_0202aab0 @ 0x0202aab0, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int);
extern int func_020b4448(void *, void *, unsigned char *);
extern const unsigned char data_020c8968[6];

int func_0202aab0(void *a, void *b, unsigned int idx)
{
    unsigned char mask;
    int avail;
    int j, i, k, base;
    unsigned char c;

    if (idx < 6) {
        base = data_020c8968[idx];
    } else {
        base = 0;
    }
    mask = 0xff;
    avail = 8;

    for (j = 0; j < 8; j++) {
        k = func_020644cc(avail);
        for (i = 0; i < 8; i++) {
            if (((mask >> i) & 1) != 0) {
                if (k == 0) {
                    c = i + base;
                    if (func_020b4448(a, b, &c) != 0) {
                        return 1;
                    }
                    mask &= ~(1 << i);
                    break;
                }
                k--;
            }
        }
        avail--;
    }
    return 0;
}
