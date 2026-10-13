/* func_020ed03c @ 0x020ed03c, 0x108 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
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
