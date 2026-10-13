/* func_020024cc @ 0x020024cc, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020024cc(void);
extern void GX_LoadBGPltt(const void *, int, int);
extern void GXS_LoadBGPltt(const void *, int, int);
extern unsigned short data_0213fdf0[];

void func_020024cc(void)
{
    GX_LoadBGPltt(data_0213fdf0, 0, 2);
    GXS_LoadBGPltt(data_0213fdf0, 0, 2);
}
