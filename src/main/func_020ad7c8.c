/* func_020ad7c8 @ 0x020ad7c8, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int arg);
extern unsigned short data_020d1e5c[];

void func_020ad7c8(unsigned short *out)
{
    *out = data_020d1e5c[func_020644cc(0xc)];
}
