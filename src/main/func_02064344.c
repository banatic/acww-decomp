/* func_02064344 @ 0x02064344, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int memcmp(const void *a, const void *b, unsigned int size);

int func_02064344(const void *a, const void *b, unsigned int size)
{
    int result;
    if (memcmp(a, b, size) != 0) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
