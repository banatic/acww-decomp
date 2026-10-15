/* func_020aefec @ 0x020aefec, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020d1e20[];
extern int func_020af028(unsigned short *);

int func_020aefec(unsigned short *argument0)
{
    int result;
    result = func_020af028((unsigned short *) argument0);
    return data_020d1e20[result];
}
