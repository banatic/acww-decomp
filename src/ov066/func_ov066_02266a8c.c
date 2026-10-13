/* func_ov066_02266a8c @ 0x02266a8c, 0x48 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern void func_ov066_02269a14(void);
extern void func_ov066_0226686c(void);
extern unsigned int *data_ov066_0226bdec;

void func_ov066_02266a8c(unsigned short *param)
{
    if (param[1] == 0) {
        data_ov066_0226bdec[1] = 4;
        func_ov066_02269a14();
    } else {
        func_ov066_0226686c();
    }
}
