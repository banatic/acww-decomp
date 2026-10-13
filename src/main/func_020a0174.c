/* func_020a0174 @ 0x020a0174, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02077b9c(void *);
extern void func_02077b70(void *, void *);
extern unsigned int data_021d11c4;
extern unsigned int SDK_OVERLAY_ov068_ID;

void func_020a0174(void)
{
    func_02077b9c(&data_021d11c4);
    func_02077b70(&data_021d11c4, &SDK_OVERLAY_ov068_ID);
}
