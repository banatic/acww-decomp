/* func_02082d1c @ 0x02082d1c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02083100(void *);
extern int data_020e1a40;

void *func_02082d1c(void *ptr)
{
    func_02083100(ptr);
    *(unsigned int *) ptr = (unsigned int) &data_020e1a40;
    return ptr;
}
