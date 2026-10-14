/* func_0206e35c @ 0x0206e35c, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#pragma arm
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
#pragma thumb

extern void func_0206dd6c(void *);

void *func_0206e35c(void *ptr)
{
    __cxa_vec_cleanup((char *) ptr + 0xe8, 4, 0x74, func_0206dd6c);
    func_0206dd6c((char *) ptr + 0x74);
    func_0206dd6c(ptr);
    return ptr;
}
