/* func_ov066_02267188 @ 0x02267188, 0x9c bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern unsigned int *data_ov066_0226bdec;

extern void func_ov066_02266b54(int);
extern void func_ov066_02268370(unsigned int);
extern void func_ov066_022682cc(void);
extern void func_ov066_02269728(void);
extern void func_ov066_02268098(void);

void func_ov066_02267188(void)
{
    switch (*data_ov066_0226bdec) {
        case 0:
        case 1:
            func_ov066_02266b54(3);
            break;
        case 3:
            func_ov066_02268370(0x0000bd8a);
            break;
        case 4:
            func_ov066_022682cc();
            break;
        case 5:
            func_ov066_02269728();
            break;
        case 6:
            func_ov066_02268098();
            break;
    }
}
