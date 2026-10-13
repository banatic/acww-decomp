/* func_020b1580 @ 0x020b1580, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b15b0(void);
extern int func_020b1974(int, int);

int func_020b1580(void)
{
    int handle;
    int i;
    handle = func_020b15b0();
    for (i = 0; i < 16; i++) {
        if (func_020b1974(handle, i) == 0) {
            return i;
        }
    }
    return -1;
}
