/* func_02010004 @ 0x02010004, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e54a8;
extern void func_ov004_02225fb8(int a, int b, int c);
extern void func_ov003_0220c328(void);

void func_02010004(int a, int b)
{
    unsigned int flag;
    flag = (data_020e54a8 == 1) ? 1 : 0;
    if (flag != 0) {
        func_ov004_02225fb8(a, b, 0);
    } else {
        func_ov003_0220c328();
    }
}
