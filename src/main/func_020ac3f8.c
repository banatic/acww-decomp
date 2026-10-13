/* func_020ac3f8 @ 0x020ac3f8, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void DC_FlushRange(void *ptr, int value);
extern void GX_LoadBGPltt(void *ptr, int value, int count);

void func_020ac3f8(void *param)
{
    unsigned char *p = (unsigned char *) param;
    if (p[0x12] != 0) {
        DC_FlushRange(p + 8, 10);
        GX_LoadBGPltt(p + 8, 0x82, 10);
        p[0x12] = 0;
    }
}
