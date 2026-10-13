/* func_020eaa6c @ 0x020eaa6c, 0x3c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int func_020eaa6c(void *r0, void *r1);

int func_020eaa6c(void *r0, void *r1)
{
    if (*(int *) r0 == *(int *) r1 && *(int *) ((char *) r0 + 4) == *(int *) ((char *) r1 + 4) &&
        *(int *) ((char *) r0 + 8) == *(int *) ((char *) r1 + 8)) {
        return 1;
    }
    return 0;
}
