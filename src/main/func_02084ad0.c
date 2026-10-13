/* func_02084ad0 @ 0x02084ad0, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b22b8(void);
extern int func_020b22dc(void);

int func_02084ad0(void)
{
    if (func_020b22b8() != 0 || func_020b22dc() != 0) {
        return 1;
    } else {
        return 0;
    }
}
