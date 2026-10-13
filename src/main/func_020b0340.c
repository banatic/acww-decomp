/* func_020b0340 @ 0x020b0340, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f4ad0;
#define gFlag (*(unsigned short *) 0x027fffa8)
extern void func_020b0300(void);
extern void func_020b02c8(void);
extern void func_020b0294(void);
extern void func_020046b4(void);
extern void PM_SetLCDPower(int arg);

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
