/* library_overlay_3: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a01b4 @ 0x020a01b4, 0x20 bytes, Thumb
 * func_020a0194 @ 0x020a0194, 0x20 bytes, Thumb
 * func_020a0174 @ 0x020a0174, 0x20 bytes, Thumb
 */

extern void func_02077b9c(void *);
extern int func_02077b70(void *, void *);
extern unsigned char data_021d11c4[];
extern unsigned char SDK_OVERLAY_ov066_ID;
extern unsigned char SDK_OVERLAY_ov065_ID;
extern unsigned int SDK_OVERLAY_ov068_ID;

void func_020a01b4(void)
{
    func_02077b9c(data_021d11c4);
    func_02077b70(data_021d11c4, &SDK_OVERLAY_ov066_ID);
}

void func_020a0194(void)
{
    func_02077b9c(((unsigned char *) data_021d11c4));
    func_02077b70(((unsigned char *) data_021d11c4), &SDK_OVERLAY_ov065_ID);
}

int func_020a0174(void)
{
    func_02077b9c(((unsigned int *) data_021d11c4));
    return func_02077b70(((unsigned int *) data_021d11c4), &SDK_OVERLAY_ov068_ID);
}
