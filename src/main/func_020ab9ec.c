/* func_020ab9ec @ 0x020ab9ec, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208f098(void *ptr);
extern void func_020ab9c8(void *ptr);

void func_020ab9ec(void *ptr)
{
    if (func_0208f098((char *) ptr + 0x6c) != 0) {
        func_020ab9c8(ptr);
    }
}
