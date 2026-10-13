/* func_020ba160 @ 0x020ba160, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void DC_FlushRange(unsigned int a, unsigned int b);
extern void GX_BeginLoadTexPltt(void);
extern void GX_LoadTexPltt(unsigned int a, unsigned int b, unsigned int c);
extern void GX_EndLoadTexPltt(void);

void func_020ba160(unsigned int *s)
{
    DC_FlushRange(s[1], s[2]);
    GX_BeginLoadTexPltt();
    GX_LoadTexPltt(s[1], s[0], s[2]);
    GX_EndLoadTexPltt();
}
