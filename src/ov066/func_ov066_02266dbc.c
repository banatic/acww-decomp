/* func_ov066_02266dbc @ 0x02266dbc, 0x4c bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int *data_ov066_0226bdec;
extern void func_ov066_0226696c(void *packet);
extern void func_ov066_02266a08(void (*)(void *));

void func_ov066_02266dbc(void)
{
    unsigned int x = data_ov066_0226bdec[1];
    switch (x) {
        case 0:
        case 1:
        case 2:
        case 3:
            break;
        default:
            func_ov066_02266a08(func_ov066_0226696c);
            break;
    }
}
