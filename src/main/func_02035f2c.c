/* func_02035f2c @ 0x02035f2c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020da2d4;
extern void func_020edb3c(void *ptr);

void *func_02035f2c(void *ptr)
{
    *(unsigned int *) ptr = (unsigned int) &data_020da2d4;
    func_020edb3c(ptr);
    return ptr;
}
