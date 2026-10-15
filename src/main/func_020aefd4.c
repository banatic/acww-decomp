/* func_020aefd4 @ 0x020aefd4, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020d1e24[];
extern int func_020af028(unsigned short *);

int func_020aefd4(unsigned short *argument0)
{
    int r0;
    r0 = func_020af028((unsigned short *) argument0);
    return data_020d1e24[r0];
}
