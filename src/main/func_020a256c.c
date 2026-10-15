/* func_020a256c @ 0x020a256c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e3b38;
extern void *func_02066994(void *ptr);

void *func_020a256c(void *ptr)
{
    *(void **) ptr = &data_020e3b38;
    func_02066994(ptr);
    return ptr;
}
