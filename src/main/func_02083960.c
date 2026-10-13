/* func_02083960 @ 0x02083960, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02083960(void *base, unsigned int index);

void *func_02083960(void *base, unsigned int index)
{
    unsigned int count;
    void *result;

    result = 0;
    count = *(unsigned int *) ((char *) base + 4);
    if (index < count) {
        result = (char *) base + 8 + index * 8;
    }
    return result;
}
