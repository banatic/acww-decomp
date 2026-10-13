/* func_020a9c9c @ 0x020a9c9c, 0xe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a9c9c(void *param);

int func_020a9c9c(void *param)
{
    if (*(int *) ((char *) param + 0x18) == 0) {
        return 1;
    }
    return 0;
}
