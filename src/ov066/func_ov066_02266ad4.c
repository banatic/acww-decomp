/* func_ov066_02266ad4 @ 0x02266ad4, 0x40 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern int *data_ov066_0226bdec;
extern void func_ov066_0226686c(unsigned short);

void func_ov066_02266ad4(unsigned short *p)
{
    unsigned short x = p[1];
    if (x == 0) {
        data_ov066_0226bdec[1] = 2;
        return;
    }
    func_ov066_0226686c(x);
}
