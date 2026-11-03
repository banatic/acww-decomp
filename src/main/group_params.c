/* group_params: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206f504 @ 0x0206f504, 0x8 bytes, Thumb
 * func_0206f4f4 @ 0x0206f4f4, 0x10 bytes, Thumb
 * func_0206f4e4 @ 0x0206f4e4, 0x10 bytes, Thumb
 */

extern void func_02051c08(void *dst, const void *src, int size);
extern void func_02051bf8(void *dst, int size);
extern unsigned char data_021cfd48[];

int func_0206f504(void)
{
    return (int) ((int *) data_021cfd48);
}

void func_0206f4f4(void *dst)
{
    func_02051c08(dst, ((const unsigned char *) data_021cfd48), 0x10);
}

void func_0206f4e4(void)
{
    func_02051bf8(data_021cfd48, 0x10);
}
