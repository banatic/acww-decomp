/* func_0208997c @ 0x0208997c, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void GX_LoadOAM(void *dst, int val, int size);
extern void GXS_LoadOAM(void *dst, int val, int size);

extern unsigned char data_021d2920[];
extern unsigned char data_021d2d20[];

void func_0208997c(void)
{
    GX_LoadOAM((void *) data_021d2920, 0, 0x400);
    GXS_LoadOAM((void *) data_021d2d20, 0, 0x400);
}
