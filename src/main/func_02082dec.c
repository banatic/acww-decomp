/* func_02082dec @ 0x02082dec, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020830d0(void *arg);
extern unsigned int data_020e1a68;

void *func_02082dec(void *ptr)
{
    *(unsigned int *) ptr = (unsigned int) &data_020e1a68;
    func_020830d0(ptr);
    return ptr;
}
