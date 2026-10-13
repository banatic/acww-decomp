/* func_020aa688 @ 0x020aa688, 0xe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020aa688(void *arg);

int func_020aa688(void *arg)
{
    if (*(int *) ((char *) arg + 8) == 0) {
        return 1;
    }
    return 0;
}
