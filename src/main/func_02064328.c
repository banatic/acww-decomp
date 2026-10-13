/* func_02064328 @ 0x02064328, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef char *va_list;
#define va_start(ap, last) ((ap) = (va_list) ((((unsigned int) &(last)) & ~3) + 4))

extern void func_02064310(int, int, va_list);

void func_02064328(int a, int b, ...)
{
    va_list ap;
    va_start(ap, b);
    func_02064310(a, b, ap);
}
