/* func_020be9dc @ 0x020be9dc, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02099194(int);

int func_020be9dc(void)
{
    if ((unsigned) func_02099194(func_020984e8()) >= 16U) {
        return 1;
    } else {
        return 0;
    }
}
