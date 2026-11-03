/* local_wireless_3: 3 functions, module ov066
 * mwccarm 1.2/base -O4,p
 * func_ov066_02266b14 @ 0x02266b14, 0x40 bytes, ARM
 * func_ov066_02266ad4 @ 0x02266ad4, 0x40 bytes, ARM
 * func_ov066_02266a8c @ 0x02266a8c, 0x48 bytes, ARM
 */

extern void func_ov066_0226686c(int status);
extern unsigned int data_ov066_0226bdec;
extern void func_ov066_02269a14(void);

void func_ov066_02266b14(unsigned short *arg0)
{
    if (arg0[1] == 0) {
        unsigned int *p = (unsigned int *) data_ov066_0226bdec;
        p[1] = 3;
        return;
    }
    func_ov066_0226686c(arg0[1]);
}

void func_ov066_02266ad4(unsigned short *p)
{
    unsigned short x = p[1];
    if (x == 0) {
        (*(int * *) &data_ov066_0226bdec)[1] = 2;
        return;
    }
    func_ov066_0226686c((unsigned short) x);
}

void func_ov066_02266a8c(unsigned short *param)
{
    if (param[1] == 0) {
        (*(unsigned int * *) &data_ov066_0226bdec)[1] = 4;
        func_ov066_02269a14();
    } else {
        func_ov066_0226686c(param[1]);
    }
}
