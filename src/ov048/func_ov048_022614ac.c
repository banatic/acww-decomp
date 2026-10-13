/* func_ov048_022614ac @ 0x022614ac, 0x30 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern int func_020eba08(void);
extern int func_020e8b0c(int, const char *, const char *);

int func_ov048_022614ac(void)
{
    int x = func_020eba08();
    if (x < 0) {
        x = -x;
    }
    return func_020e8b0c(x, (const char *) 0x00017ed0, (const char *) 0x000182b7) != 0;
}
