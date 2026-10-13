/* func_020abaec @ 0x020abaec, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *ptr);
extern void func_020abbf8(void *ptr);

void func_020abaec(void *ptr)
{
    if (func_0208e484((char *) ptr + 0x20)) {
        func_020abbf8(ptr);
    }
}
