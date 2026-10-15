/* func_02068034 @ 0x02068034, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b44a4(unsigned char *dest, unsigned char value);

unsigned char *func_02068034(unsigned char *arg)
{
    func_020b44a4(arg + 0x1b14, arg[0x1a68]);
    return arg + 0x1b14;
}
