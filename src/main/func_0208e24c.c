/* func_0208e24c @ 0x0208e24c, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208e24c(void);
extern unsigned char data_020d0adc[];
extern void GX_LoadOBJPltt(void *dst, int size, int value);

void func_0208e24c(void)
{
    GX_LoadOBJPltt(data_020d0adc, 0xbc, 2);
}
