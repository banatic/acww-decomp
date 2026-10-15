/* func_020aefa4 @ 0x020aefa4, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020d1e2c[];
extern int func_020af028(unsigned short *);

int func_020aefa4(unsigned short *argument0)
{
    unsigned char result;
    int index;

    index = func_020af028((unsigned short *) argument0);
    result = data_020d1e2c[index];
    return result;
}
