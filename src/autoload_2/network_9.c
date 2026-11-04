/* network_9: 3 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020eba08 @ 0x020eba08, 0x10 bytes, ARM
 * func_020eb9fc @ 0x020eb9fc, 0xc bytes, ARM
 * func_020eb9f0 @ 0x020eb9f0, 0xc bytes, ARM
 */

extern int data_021fbf24;
extern void func_ov065_022784a0(void);
extern int func_ov066_02269638(const void *src, unsigned int length);

int func_020eba08(void)
{
    return data_021fbf24;
}

void func_020eb9fc(void)
{
    func_ov065_022784a0();
}

int func_020eb9f0(const void *src, unsigned int length)
{
    return func_ov066_02269638(src, length);
}
