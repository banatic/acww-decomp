/* func_ov118_0229ae90 @ 0x0229ae90, 0x68 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern const unsigned char *func_ov118_0229b3b0(int);
extern const unsigned char data_ov118_0229ca90[];

unsigned char func_ov118_0229ae90(int a, unsigned int b)
{
    unsigned char r1;
    const unsigned char *p;
    if (b >= 1 && b < 15) {
        return (unsigned char) (b - 1);
    }
    if (b >= 15 && b < 28) {
        p = func_ov118_0229b3b0(a);
        r1 = p[b - 15];
        if (r1 == 0) {
            return 14;
        }
        if (r1 == 1 || (r1 >= 2 && r1 < 6)) {
            return 8;
        }
        if (r1 >= 6 && r1 < 14) {
            return (unsigned char) (r1 - 6);
        }
        if (r1 >= 14 && r1 < 19) {
            return data_ov118_0229ca90[r1 - 14];
        }
    }
    return 14;
}
