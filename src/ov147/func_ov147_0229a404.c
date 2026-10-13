/* func_ov147_0229a404 @ 0x0229a404, 0x1a bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

extern void DC_FlushRange(void *dst, int size);
extern void GX_LoadBGPltt(void *dst, int size, int value);

void func_ov147_0229a404(void *dst)
{
    DC_FlushRange(dst, 0x20);
    GX_LoadBGPltt(dst, 0x20, 0x20);
}
