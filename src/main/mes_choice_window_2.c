/* mes_choice_window_2: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020ac240 @ 0x020ac240, 0x1a bytes, Thumb
 * func_020ac218 @ 0x020ac218, 0x26 bytes, Thumb
 */

extern int func_0208e4bc(int);
extern int func_0208e484(void *);

int func_020ac240(int param)
{
    int result;
    if (func_0208e4bc(param + 0x20) == 7) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

int func_020ac218(void *param)
{
    if (func_0208e4bc((int) ((char *) param + 0x20)) == 8 && func_0208e484((char *) param + 0x20) != 0) {
        return 1;
    } else {
        return 0;
    }
}
