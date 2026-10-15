/* func_020aef2c @ 0x020aef2c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020d1e30[];
extern int func_020af028(unsigned short *);

int func_020aef2c(unsigned short *argument0)
{
    int result;
    result = func_020af028((unsigned short *) argument0);
    return data_020d1e30[result];
}
