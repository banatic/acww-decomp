/* func_020b0294 @ 0x020b0294, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int PM_GetLCDPower(void);
extern int PM_SetLCDPower(int);
extern int func_020b027c(int);
extern void func_020046a4(void);

extern volatile unsigned char data_021f4ad0;

void func_020b0294(void)
{
    if (PM_GetLCDPower() != 1) {
        if (PM_SetLCDPower(1) == 0) {
            return;
        }
    }
    if (func_020b027c(2) == 0) {
        func_020046a4();
    }
    data_021f4ad0 = 0;
}
