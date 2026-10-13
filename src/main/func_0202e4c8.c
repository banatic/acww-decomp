/* func_0202e4c8 @ 0x0202e4c8, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208150c(void);
extern int func_02003648(void);

int func_0202e4c8(void *param)
{
    if (((*(unsigned short *) ((char *) param + 0xEA) & 0xF000) >> 12) == 0xE) {
        if (*(int *) ((char *) param + 0x830) != 0) {
            func_0208150c();
            return func_02003648();
        }
    }
    return 0xFFFF;
}
