/* func_ov144_02299c8c @ 0x02299c8c, 0x38 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

void func_ov144_02299c8c(unsigned char *base, unsigned short value)
{
    int idx;
    int k;
    int j;
    int i;

    idx = 0x82;
    for (i = 4; i <= 7; i++) {
        k = idx;
        for (j = 2; j <= 5; j++) {
            *(unsigned short *) (base + 2 * k + 0x190a) = value;
            k++;
            value++;
        }
        idx += 0x20;
    }
}
