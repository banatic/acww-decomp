/* func_020578d4 @ 0x020578d4, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b9ec4(void *ptr);
void *func_020578d4(void *ptr)
{
    func_020b9ec4(ptr);
    func_020b9ec4((char *) ptr + 0x1c);
    return ptr;
}
