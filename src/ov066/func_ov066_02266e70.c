/* func_ov066_02266e70 @ 0x02266e70, 0x108 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern struct UnkStruct_02266e70 {
    unsigned int unk_00;
    unsigned int cmd;
} *data_ov066_0226bdec;

extern void func_ov066_0226686c(int);
extern void func_ov066_0226727c(void);
extern void func_ov066_02267224(void);
extern void func_ov066_02267188(void);
extern void func_ov066_02267138(void);
extern void func_ov066_022670d8(void);
extern void func_ov066_02267088(void);
extern void func_ov066_02267038(void);
extern void func_ov066_02266e64(void);
extern void func_ov066_02266fd8(void);
extern void func_ov066_02266f78(void);

void func_ov066_02266e70(void)
{
    unsigned int cmd;
    cmd = data_ov066_0226bdec->cmd;
    switch (cmd) {
        case 2:
            func_ov066_0226727c();
            break;
        case 3:
            func_ov066_02267224();
            break;
        case 4:
            func_ov066_02267188();
            break;
        case 6:
            func_ov066_02267138();
            break;
        case 7:
            func_ov066_022670d8();
            break;
        case 8:
            func_ov066_02267088();
            break;
        case 5:
            func_ov066_02267038();
            break;
        case 10:
            func_ov066_02266fd8();
            break;
        case 11:
            func_ov066_02266f78();
            break;
        case 0:
        case 1:
            func_ov066_0226686c(0x44);
            break;
        case 9:
        default:
            func_ov066_02266e64();
            break;
    }
}
