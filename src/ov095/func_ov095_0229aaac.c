/* func_ov095_0229aaac @ 0x0229aaac, 0x34 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov095_0229ac2c(void);
extern unsigned char data_ov095_0229d020[];
extern unsigned char data_ov095_0229cff0[];

void func_ov095_0229aaac(void *self)
{
    if (func_ov095_0229ac2c() == 0) {
        int v = *(int *) ((char *) self + 0x28);
        if (v >= 0xc9 && v <= 0xf6) {
            int idx = v - 0xc9;
            *(int *) ((char *) self + 0x2c) = data_ov095_0229d020[idx];
            *(int *) ((char *) self + 0x30) = data_ov095_0229cff0[idx];
        }
    }
}
