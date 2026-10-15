/* func_ov068_022720b4 @ 0x022720b4, 0x50 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern short data_ov068_022786c8;
extern void func_0203e328(void);
extern int func_020b5e10(void);
extern int func_020b6434(int, int, int, int);
extern int func_020984e8(void);
extern void func_02099a38(void *argument0);
extern int func_020984d4(void);
extern void func_0209ef10(int, int);

extern unsigned char data_021dc7a8[];

void func_ov068_022720b4(void *receiver)
{
    if (data_ov068_022786c8 == 0) {
        func_0203e328();
        func_020b6434(func_020b5e10(), 0x2c, 2, 2);

        func_02099a38((void *) func_020984e8());
        func_0209ef10((unsigned int) data_021dc7a8, func_020984d4());
    }
    if (data_ov068_022786c8 >= 0) {
        data_ov068_022786c8--;
    }
}
