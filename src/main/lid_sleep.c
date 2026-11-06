/* lid_sleep: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b03ac @ 0x020b03ac, 0x14 bytes, Thumb
 * func_020b0340 @ 0x020b0340, 0x6c bytes, Thumb
 * func_020b0334 @ 0x020b0334, 0xc bytes, Thumb
 * func_020b0300 @ 0x020b0300, 0x34 bytes, Thumb
 * func_020b02c8 @ 0x020b02c8, 0x38 bytes, Thumb
 * func_020b0294 @ 0x020b0294, 0x34 bytes, Thumb
 * func_020b027c @ 0x020b027c, 0x18 bytes, Thumb
 */

#define gFlag (*(unsigned short *) 0x027fffa8)

extern unsigned char data_021f4ad0;
extern void func_020046b4(void);
extern int PM_SetLCDPower(int arg);
extern void func_020b026c(int);
extern unsigned int PM_GetBackLight(int, int);
extern int func_0211dc78(int, int);
extern unsigned char data_021f4ad4[];
extern unsigned char data_021f4ad8[];
extern void func_020b025c(int);
extern int PM_GetLCDPower(void);
extern void func_020046a4(void);
extern unsigned char data_021f4acc[];

void func_020b0300(void);
void func_020b02c8(void);
void func_020b0294(void);
int func_020b027c(unsigned char arg_0);

void func_020b03ac(void)
{
    (*(unsigned char *) data_021f4acc) = 0;
    data_021f4ad0 = 0;
}

void func_020b0340(void)
{
    switch (data_021f4ad0) {
        case 0:
            if (((gFlag & 0x8000) >> 15) != 0) {
                data_021f4ad0 = 1;
                func_020b0300();
                PM_SetLCDPower(0);
                func_020046b4();
            }
            break;
        case 1:
            if (((gFlag & 0x8000) >> 15) == 0) {
                data_021f4ad0 = 2;
                func_020b02c8();
                func_020b0294();
            }
            break;
        case 2:
            func_020b0294();
            break;
    }
}

void func_020b0334(void)
{
    func_020b026c(2);
}

void func_020b0300(void)
{
    int r0;
    int r1;

    r0 = func_020b027c(1);
    if (r0 == 0) {
        PM_GetBackLight((unsigned int) data_021f4ad8, (unsigned int) data_021f4ad4);
        func_0211dc78(2, 0);
        func_020b026c(1);
    }
}

void func_020b02c8(void)
{
    if (func_020b027c(1)) {
        func_0211dc78(0, (int) ((*(void **) data_021f4ad8)));
        func_0211dc78(1, (int) ((*(void **) data_021f4ad4)));
        func_020b025c(1);
    }
}

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
    (*(volatile unsigned char *) &data_021f4ad0) = 0;
}

int func_020b027c(unsigned char arg_0)
{
    unsigned char temp;
    unsigned char *ptr;

    ptr = (unsigned char *) data_021f4acc;
    temp = *ptr;
    temp &= arg_0;
    if (temp != 0) {
        return 1;
    }
    return 0;
}
