/* talk_object_5: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020676c4 @ 0x020676c4, 0x4 bytes, Thumb
 * func_020676ac @ 0x020676ac, 0x18 bytes, Thumb
 */

void func_020676c4(int *p0, int p1)
{
    p0[4] = p1;
}

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
