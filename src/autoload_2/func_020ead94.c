/* func_020ead94 @ 0x020ead94, 0xac bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int func_020edaf0(int, int);
extern void func_020ed17c(void);
extern void func_020ed168(void);
extern void func_ov067_02268990(int, void (*)(void), int);
extern void WXC_SetParentParameter(int, int, int);
extern void func_ov067_02268688(void *, void (*)(void), int, int, int, int);

extern unsigned char data_021fbef8;
extern unsigned int data_021fbf48;
extern unsigned int data_021fbf50;
extern unsigned int data_021fbf28;
extern void *data_021fbf20;

void func_020ead94(int a, int b, int c)
{
    int result;

    data_021fbef8 = 5;
    data_021fbf48 = 0;
    data_021fbf50 = 0;

    result = func_020edaf0(0xa000, 0x20);
    data_021fbf28 = result;

    func_ov067_02268990(result, func_020ed17c, 2);
    WXC_SetParentParameter(0x3c, 0x3c, 1);

    func_ov067_02268688(data_021fbf20, func_020ed168, a, c, b, c);
}
