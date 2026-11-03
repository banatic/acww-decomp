/* oam_buffer_3: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208997c @ 0x0208997c, 0x2c bytes, Thumb
 * func_02089954 @ 0x02089954, 0x28 bytes, Thumb
 */

extern void GX_LoadOAM(void *dst, int val, int size);
extern void GXS_LoadOAM(void *dst, int val, int size);
extern unsigned char data_021d2920[];
extern unsigned char data_021d2d20[];
extern void DC_FlushRange(void *dest, unsigned int size);

void func_0208997c(void)
{
    GX_LoadOAM((void *) data_021d2920, 0, 0x400);
    GXS_LoadOAM((void *) data_021d2d20, 0, 0x400);
}

void func_02089954(void)
{
    DC_FlushRange((void *) data_021d2920, 0x400);
    DC_FlushRange((void *) data_021d2d20, 0x400);
}
