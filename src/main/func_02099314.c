/* func_02099314 @ 0x02099314, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02099a28(void *ptr);

int func_02099314(void *ptr, int count)
{
    int i = 0;
    int result = -1;
    void *p = ptr;

    while (i < count) {
        if (func_02099a28(p) == 0) {
            result = i;
            break;
        }
        p = (char *) p + 0x249c;
        i++;
    }
    return result;
}
