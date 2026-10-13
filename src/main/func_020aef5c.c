/* func_020aef5c @ 0x020aef5c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020d1e1c[];
extern int func_020af028(void);

int func_020aef5c(void)
{
    int result;
    unsigned char value;

    result = func_020af028();
    value = data_020d1e1c[result];
    return value;
}
