/* func_020aef74 @ 0x020aef74, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020d1e10[];
extern unsigned char func_020af028(void);

unsigned char func_020aef74(void)
{
    unsigned char result;
    unsigned char index;

    index = func_020af028();
    result = data_020d1e10[index];
    return result;
}
