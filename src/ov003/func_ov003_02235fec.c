/* func_ov003_02235fec @ 0x02235fec, 0x3a bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

int func_ov003_02235fec(char *base)
{
    int n;
    unsigned int a, b;
    n = 0;
    for (a = 0; a < 4; a++) {
        for (b = 0; b < 4; b++) {
            if (*(unsigned short *) (base + a * 0x88 + b * 0x22 + 0x20) != 0) {
                n++;
            }
        }
    }
    return n;
}
