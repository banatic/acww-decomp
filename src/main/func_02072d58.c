/* func_02072d58 @ 0x02072d58, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02072d58(unsigned int *dest, unsigned int value)
{
    unsigned int pattern = (unsigned char) (value | (value << 4));
    unsigned int word = (pattern << 24) | ((pattern << 16) | ((pattern << 8) | pattern));
    unsigned int *p = dest;
    unsigned int *end = (unsigned int *) ((unsigned char *) dest + 0x200);
    while (p < end) {
        *p++ = word;
    }
}
