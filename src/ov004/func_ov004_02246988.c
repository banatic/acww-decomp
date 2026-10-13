/* func_ov004_02246988 @ 0x02246988, 0x54 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_ov004_0225ff50;
extern void *data_ov004_0225ff54;
extern void *data_021c9b28;
extern int SDK_OVERLAY_ov093_ID;
extern void func_ov093_0229959c(void *);
extern void func_ov093_022997b4(void *);
extern void func_020e993c(void *, void *);
extern void func_0204f8ec(int);
void func_ov004_02246988(void)
{
    void *h;
    if (data_ov004_0225ff50 & 1) {
        func_ov093_0229959c(data_ov004_0225ff54);
        h = data_021c9b28;
        func_ov093_022997b4(data_ov004_0225ff54);
        func_020e993c(h, data_ov004_0225ff54);
        data_ov004_0225ff54 = 0;
        func_0204f8ec((int) &SDK_OVERLAY_ov093_ID);
    }
    data_ov004_0225ff50 = 0;
}
