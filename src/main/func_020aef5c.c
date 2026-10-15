/* func_020aef5c @ 0x020aef5c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020d1e1c[];
extern int func_020af028(unsigned short *);

int func_020aef5c(unsigned short *argument0)
{
    int result;
    unsigned char value;

    result = func_020af028((unsigned short *) argument0);
    value = data_020d1e1c[result];
    return value;
}
