/* func_ov004_0220fefc @ 0x0220fefc, 0x50 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0220ff4c(void *self, int *p, unsigned i);
extern void VEC_Add(int *a, int *b, int *d);

void func_ov004_0220fefc(char *self, int *out)
{
    int acc[3];
    int tmp[3];
    unsigned i;

    acc[0] = 0;
    acc[1] = 0;
    acc[2] = 0;
    for (i = 0; i < 4; i++) {
        func_ov004_0220ff4c(self, tmp, i);
        VEC_Add(acc, tmp, acc);
    }
    acc[0] = acc[0] >> 2;
    acc[1] = acc[1] >> 2;
    acc[2] = acc[2] >> 2;
    out[0] = acc[0];
    out[1] = acc[1];
    out[2] = acc[2];
}
