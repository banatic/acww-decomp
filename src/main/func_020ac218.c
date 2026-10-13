/* func_020ac218 @ 0x020ac218, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e4bc(void *);
extern int func_0208e484(void *);

int func_020ac218(void *param)
{
    if (func_0208e4bc((char *) param + 0x20) == 8 && func_0208e484((char *) param + 0x20) != 0) {
        return 1;
    } else {
        return 0;
    }
}
