/* func_020a0174 @ 0x020a0174, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02077b9c(void *);
extern int func_02077b70(void *, void *);
extern unsigned int data_021d11c4;
extern unsigned int SDK_OVERLAY_ov068_ID;

int func_020a0174(void)
{
    func_02077b9c(&data_021d11c4);
    return func_02077b70(&data_021d11c4, &SDK_OVERLAY_ov068_ID);
}
