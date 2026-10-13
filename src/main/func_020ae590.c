/* func_020ae590 @ 0x020ae590, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209f150(void *, int);
extern int data_021dc7a8;

int func_020ae590(signed char *s)
{
    if (s[4] != -1) {
        if (func_0209f150(&data_021dc7a8, 8) == 0) {
            return 1;
        }
    }
    return 0;
}
