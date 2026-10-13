/* func_02056910 @ 0x02056910, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02057054(void *ptr);
extern char data_020dd164;

void *func_02056910(void *ptr)
{
    *(void **) ptr = (void *) &data_020dd164;
    func_02057054(ptr);
    return ptr;
}
