/* func_020aef8c @ 0x020aef8c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020d1e18[];
extern int func_020af028(void);

unsigned char func_020aef8c(void)
{
    unsigned char result;
    int index;

    index = func_020af028();
    result = data_020d1e18[index];
    return result;
}
