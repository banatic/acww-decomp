/* func_02082f60 @ 0x02082f60, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02083100(void *);
extern unsigned int data_020e19f0;

void *func_02082f60(void *ptr)
{
    func_02083100(ptr);
    *(unsigned int *) ptr = (unsigned int) &data_020e19f0;
    return ptr;
}
