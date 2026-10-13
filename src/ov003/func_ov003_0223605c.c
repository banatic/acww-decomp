/* func_ov003_0223605c @ 0x0223605c, 0x5a bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int n);
extern int func_ov003_022360b8(unsigned short *p, int i, int j);

int func_ov003_0223605c(unsigned short *p, int *ox, int *oz)
{
    int k;
    unsigned int z, x;
    int n;
    if (p[0x10] != 0) {
        n = func_020644cc(p[0x10]);
        k = 0;
        for (z = 0; z < 0x10; z++) {
            for (x = 0; x < 0x10; x++) {
                if (func_ov003_022360b8(p, x, z) == 0) {
                    if (n == k) {
                        *ox = x;
                        *oz = z;
                        return 1;
                    }
                    k++;
                }
            }
        }
    }
    return 0;
}
