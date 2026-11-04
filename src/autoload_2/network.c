/* network: 6 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020eae40 @ 0x020eae40, 0x40 bytes, ARM
 * func_020ead94 @ 0x020ead94, 0xac bytes, ARM
 * func_020ead88 @ 0x020ead88, 0xc bytes, ARM
 * func_020ead7c @ 0x020ead7c, 0xc bytes, ARM
 * func_020ead58 @ 0x020ead58, 0x24 bytes, ARM
 * func_020ead48 @ 0x020ead48, 0x10 bytes, ARM
 */

extern unsigned char data_021fbef8;
extern int data_021fbf34;
extern void *func_ov065_0227e67c(void);
extern int func_020edaf0(int, int);
extern void func_020ed17c(int state, void *user_data);
extern void func_020ed168(void);
extern void func_ov067_02268990(int, void (*)(int, void *), int);
extern int WXC_SetParentParameter(int, int, int);
extern int func_ov067_02268688(void *, void (*)(void), int, int, int, int);
extern unsigned int data_021fbf48;
extern unsigned int data_021fbf50;
extern unsigned int data_021fbf28;
extern void *data_021fbf20;
extern void WXC_Start(void);
extern void func_ov067_0226883c(void);
extern int WXC_GetStateCode(void);

int func_020eae40(void)
{
    if (data_021fbef8 == 3) {
        data_021fbf34 = 0;
        func_ov065_0227e67c();
    }
    return 1;
}

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

void func_020ead88(void)
{
    WXC_Start();
}

void func_020ead7c(void)
{
    func_ov067_0226883c();
}

int func_020ead58(void)
{
    int result;
    result = WXC_GetStateCode();
    if (result == 2) {
        return 1;
    } else {
        return 0;
    }
}

unsigned int func_020ead48(void)
{
    return data_021fbf50;
}
