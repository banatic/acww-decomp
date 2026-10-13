/* func_02083424 @ 0x02083424, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void *func_02083424(void *base, unsigned int index)
{
    void *ret = 0;
    if (index < *(unsigned int *) ((char *) base + 4)) {
        ret = (char *) base + 8 + (index * 2);
    }
    return ret;
}
