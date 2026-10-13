/* func_02082d58 @ 0x02082d58, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e19dc;
extern void func_020830d0(void *);
extern void func_020edb3c(void *);

void *func_02082d58(void *ptr)
{
    *(void **) ptr = (void *) &data_020e19dc;
    func_020830d0(ptr);
    func_020edb3c(ptr);
    return ptr;
}
