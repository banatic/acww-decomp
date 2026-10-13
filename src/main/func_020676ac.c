/* func_020676ac @ 0x020676ac, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020676ac(void *self);

int func_020676ac(void *self)
{
    int result;
    int count;
    int new_count;

    result = 0;
    count = *(int *) ((char *) self + 0x10);
    if (count > 0) {
        new_count = count - 1;
        *(int *) ((char *) self + 0x10) = new_count;
        if (*(int *) ((char *) self + 0x10) == 0) {
            result = 1;
        }
    }
    return result;
}
