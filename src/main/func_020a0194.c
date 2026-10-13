/* func_020a0194 @ 0x020a0194, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02077b9c(void *ptr);
extern void func_02077b70(void *ptr1, void *ptr2);

extern unsigned char data_021d11c4;
extern unsigned char SDK_OVERLAY_ov065_ID;

void func_020a0194(void)
{
    func_02077b9c(&data_021d11c4);
    func_02077b70(&data_021d11c4, &SDK_OVERLAY_ov065_ID);
}
