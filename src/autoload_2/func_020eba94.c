/* func_020eba94 @ 0x020eba94, 0x19c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern int DWC_GetLastError(unsigned int *);
extern unsigned int data_021fbf24;
extern struct Entry {
    unsigned char pad_00[2];
    unsigned char flag;
    unsigned char pad_03;
} data_021fbff8[16];

int func_020eba94(void)
{
    int ret = DWC_GetLastError(&data_021fbf24);
    if (ret != 0) {
        switch (ret) {
            case 1:
                return 0x4001;
            case 2:
                return 0x4002;
            case 3:
                return 0x4003;
            case 4:
                return 0x4004;
            case 5:
                return 0x4005;
            case 6:
                return 0x4006;
            case 9:
                return 0x4009;
            case 10:
                return 0x400a;
            case 7:
                return 0x4007;
            case 11:
                return 0x400b;
            case 8:
                return 0x4008;
            default:
                return 0xffff;
        }
    } else {
        unsigned int i;
        for (i = 0; i < 16; i++) {
            if ((unsigned int) data_021fbff8[i].flag > 30u) {
                data_021fbf24 = 1000000;
                return 0x4007;
            }
        }
        return 0;
    }
}
