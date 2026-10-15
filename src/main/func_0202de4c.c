/* func_0202de4c @ 0x0202de4c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0201615c(void *ptr);
extern char data_020d9df8;

void *func_0202de4c(void *ptr)
{
    *(void **) ptr = &data_020d9df8;
    func_0201615c(ptr);
    return ptr;
}
