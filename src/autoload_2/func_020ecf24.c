/* func_020ecf24 @ 0x020ecf24, 0xc8 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern unsigned char data_021fbef8;
extern int DWC_GetMOSCConnectBlockState(void);
extern unsigned int data_021fbf34;
extern unsigned long long OS_GetTick(void);
extern void func_ov065_0227e67c(void);

static __inline unsigned int check(unsigned long long diff)
{
    return diff > 0x1d4c0;
}

void func_020ecf24(void)
{
    unsigned long long raw;
    unsigned long long q;

    if (data_021fbef8 != 3) {
        return;
    }
    if (DWC_GetMOSCConnectBlockState() == 0) {
        return;
    }
    if (data_021fbf34 == 0) {
        return;
    }

    raw = OS_GetTick();
    q = (raw << 6) / 0x82ea;
    if (check(q - (unsigned long long) data_021fbf34) != 0) {
        data_021fbf34 = 0;
        func_ov065_0227e67c();
    }
}
