/* func_0208053c @ 0x0208053c, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern const void *func_02095040(const void *);
extern int memcmp(const void *, const void *, unsigned int);

int func_0208053c(const void *a, const void *b)
{
    const void *p = func_02095040(a);

    if (*(const unsigned short *) b != *(const unsigned short *) p ||
        memcmp((const char *) b + 2, (const char *) p + 2, 12) != 0) {
        return 1;
    }
    return 0;
}
