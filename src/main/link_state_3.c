/* link_state_3: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a6c7c @ 0x020a6c7c, 0x10 bytes, Thumb
 * func_020a6c6c @ 0x020a6c6c, 0x10 bytes, Thumb
 */

extern void func_020a6998(int *arg0);
extern void func_020a6a74(void *ptr, int arg);
extern unsigned char data_021f4320[];

void func_020a6c7c(void)
{
    func_020a6998(((int *) data_021f4320));
}

void func_020a6c6c(int arg)
{
    func_020a6a74((void *) data_021f4320, arg);
}
