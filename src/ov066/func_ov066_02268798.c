/* func_ov066_02268798 @ 0x02268798, 0x5c bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern int func_ov066_02266e08(void);
extern void func_ov066_022686f0(void);
extern void func_ov066_0226686c(int status);
extern unsigned int data_ov066_0226bdf4;

void func_ov066_02268798(unsigned short *param)
{
    unsigned int *p;
    int v;

    if (func_ov066_02266e08() == 0) {
        if (param[1] == 0) {
            p = (unsigned int *) data_ov066_0226bdf4;
            v = *(unsigned int *) ((char *) p + 0xc0);
            v = (v << 0x1a) >> 0x1f;
            if (v != 0) {
                func_ov066_022686f0();
            }
        } else {
            func_ov066_0226686c(param[1]);
        }
    }
}
