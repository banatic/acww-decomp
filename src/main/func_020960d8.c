/* func_020960d8 @ 0x020960d8, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02096718(void);

int func_020960d8(void)
{
    int result;
    int *ptr;

    result = func_02096718();
    if (result != 0) {
        result = *(int *) ((char *) result + 0x7f0);
    } else {
        result = 0x93;
    }
    return result;
}
