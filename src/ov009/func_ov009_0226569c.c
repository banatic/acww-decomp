/* func_ov009_0226569c @ 0x0226569c, 0x20 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov009_02265630(void *element);
extern unsigned char data_ov009_02265cb4[];
extern void __cxa_vec_cleanup(const void *ptr, int a, int b, void (*cb)(void *));

void func_ov009_0226569c(void)
{
    __cxa_vec_cleanup(data_ov009_02265cb4, 0x22, 0x50, func_ov009_02265630);
}
