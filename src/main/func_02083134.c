/* func_02083134 @ 0x02083134, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void *func_02083134(char *p, unsigned int i)
{
    void *result = 0;
    if (i < *(unsigned int *) (p + 4)) {
        result = p + 8 + 108 * i;
    }
    return result;
}
