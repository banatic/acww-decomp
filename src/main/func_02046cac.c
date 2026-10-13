/* func_02046cac @ 0x02046cac, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021f3a86[15];
extern char data_021dc7a8[];

void func_02046cac(void)
{
    unsigned short *in = data_021f3a86;
    int j;

    for (j = 0; j < 15; in++, j++) {
        unsigned short val = *in;
        if (val < 0x1531 || val > 0x153a) {
            continue;
        }
        {
            int r;
            if (val >= 0x1531 && val <= 0x153a) {
                r = val - 0x1531;
            } else {
                r = -1;
            }
            {
                unsigned short out;
                if ((unsigned int) r < 10) {
                    out = (unsigned short) (0x154a + r);
                } else {
                    out = 0x154a;
                }
                *(unsigned short *) (data_021dc7a8 + j * 2 + 0x172de) = out;
            }
        }
    }
}
