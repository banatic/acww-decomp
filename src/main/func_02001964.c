/* func_02001964 @ 0x02001964, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef char *va_list;
#define va_start(ap, last) ((ap) = (char *) ((((unsigned int) (&(last))) & ~3) + sizeof(last)))
#define va_end(ap) ((void) 0)

extern char data_020d34e0[];
extern void func_02001988(void *, int, const char *, va_list);

void func_02001964(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    func_02001988(data_020d34e0, 0, fmt, ap);
    va_end(ap);
}
