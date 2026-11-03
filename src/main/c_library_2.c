/* c_library_2: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02064344 @ 0x02064344, 0x18 bytes, Thumb
 * func_02064328 @ 0x02064328, 0x1c bytes, Thumb
 */

#define va_start(ap, last) ((ap) = (va_list) ((((unsigned int) &(last)) & ~3) + 4))

typedef char *va_list;

extern int memcmp(const void *a, const void *b, unsigned int size);
extern int func_02064310(int, int, va_list);

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

int func_02064328(int a, int b, ...)
{
    va_list ap;
    va_start(ap, b);
    return func_02064310(a, b, ap);
}
