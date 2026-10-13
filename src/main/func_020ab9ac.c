/* func_020ab9ac @ 0x020ab9ac, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *ptr);
extern void func_020ab994(void *ptr);

void func_020ab9ac(void *ptr)
{
    if (func_0208e484((char *) ptr + 0x20)) {
        func_020ab994(ptr);
    }
}
