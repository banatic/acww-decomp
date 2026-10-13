/* func_ov004_02246a2c @ 0x02246a2c, 0x48 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

// Overlay ids are linker symbols, so the id comes from the literal pool.
extern void func_0204f934(int);
extern int SDK_OVERLAY_ov093_ID;
extern void *data_021c9b28;
extern void *func_020e9948(void *, unsigned long);
extern void func_ov093_022997f8(void *);
extern void func_ov093_0229976c(void *);
extern void *data_ov004_0225ff54;
extern unsigned char data_ov004_0225ff50;
void func_ov004_02246a2c(void)
{
    func_0204f934((int) &SDK_OVERLAY_ov093_ID);
    data_ov004_0225ff54 = func_020e9948(data_021c9b28, 0x2520);
    if (data_ov004_0225ff54 != 0) {
        func_ov093_022997f8(data_ov004_0225ff54);
    }
    func_ov093_0229976c(data_ov004_0225ff54);
    data_ov004_0225ff50 = 1;
}
