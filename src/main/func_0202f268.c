/* func_0202f268 @ 0x0202f268, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_0202f268(void *dst, const void *src, unsigned int size)
{
    unsigned int *d = (unsigned int *) dst;
    const unsigned int *s = (const unsigned int *) src;
    d[0] = s[0];
    d[1] = s[1];
    d[2] = s[2];
    d[3] = size;
}
