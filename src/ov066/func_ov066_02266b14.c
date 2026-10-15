/* func_ov066_02266b14 @ 0x02266b14, 0x40 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern void func_ov066_0226686c(int status);
extern unsigned int data_ov066_0226bdec;

void func_ov066_02266b14(unsigned short *arg0)
{
    if (arg0[1] == 0) {
        unsigned int *p = (unsigned int *) data_ov066_0226bdec;
        p[1] = 3;
        return;
    }
    func_ov066_0226686c(arg0[1]);
}
