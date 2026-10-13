/* func_020aef44 @ 0x020aef44, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020d1e14[];
extern int func_020af028(void);

int func_020aef44(void)
{
    int index;
    unsigned char result;

    index = func_020af028();
    result = data_020d1e14[index];
    return result;
}
