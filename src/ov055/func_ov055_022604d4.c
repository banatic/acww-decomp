/* func_ov055_022604d4 @ 0x022604d4, 0x20 bytes, Thumb, module ov055
 * mwccarm 1.2/base -O4,s
 */

extern void func_02077b9c(void *);
extern void func_02077b70(void *, void *);
extern unsigned int data_021d11c4;
extern unsigned int SDK_OVERLAY_ov068_ID;

void func_ov055_022604d4(void)
{
    func_02077b9c(&data_021d11c4);
    func_02077b70(&data_021d11c4, &SDK_OVERLAY_ov068_ID);
}
