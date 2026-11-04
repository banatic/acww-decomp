/* network_15: 3 functions, module autoload_2
 * mwccarm 1.2/base -O4,p
 * func_020ed03c @ 0x020ed03c, 0x108 bytes, ARM
 * func_020ecfec @ 0x020ecfec, 0x50 bytes, ARM
 * func_020ecf24 @ 0x020ecf24, 0xc8 bytes, ARM
 */

typedef struct {
    unsigned short val;
    unsigned char flag;
} Entry;

extern unsigned short data_021fbefc;
extern unsigned char data_021fbef4;
extern unsigned char data_0213e6b0;
extern Entry data_021fbff8[];
extern unsigned long long OS_GetTick(void);
extern int DWC_GetMyAID(void);
extern int DWC_IsValidAID(int);
extern void DWC_Ping(int);
extern unsigned char data_021fbef8;
extern int data_021fbf34;
extern int DWC_SetMatchingOption(int, const void *, int);
extern int DWC_GetMOSCConnectBlockState(void);
extern void *func_ov065_0227e67c(void);

void func_020ed03c(void)
{
    unsigned long long x;
    unsigned char new_val;

    if (data_021fbefc < 5) {
        return;
    }

    x = OS_GetTick();
    x = (x << 6) / 33514 / 250;
    new_val = (unsigned char) (x % (int) data_021fbef4);

    if (data_0213e6b0 == new_val) {
        return;
    }

    data_0213e6b0 = new_val;

    if (new_val != DWC_GetMyAID()) {
        if (DWC_IsValidAID(new_val) != 0) {
            data_021fbff8[new_val].flag++;
            DWC_Ping(new_val);
        } else {
            data_021fbff8[new_val].val = 0xffff;
            data_021fbff8[new_val].flag = 0;
        }
    } else {
        data_021fbff8[new_val].val = 0;
        data_021fbff8[new_val].flag = 0;
    }
}

void func_020ecfec(void)
{
    unsigned char val = data_021fbef8;
    data_021fbf34 = 0;
    if (val != 3) {
        return;
    }
    {
        int x = 1;
        DWC_SetMatchingOption(1, &x, 0);
    }
}

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
    if ((*(unsigned int *) &data_021fbf34) == 0) {
        return;
    }

    raw = OS_GetTick();
    q = (raw << 6) / 0x82ea;
    if (check(q - (unsigned long long) (*(unsigned int *) &data_021fbf34)) != 0) {
        (*(unsigned int *) &data_021fbf34) = 0;
        func_ov065_0227e67c();
    }
}
