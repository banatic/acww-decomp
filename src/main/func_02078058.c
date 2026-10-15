/* func_02078058 @ 0x02078058, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a88ec(void *ptr);
extern int data_020e1870;

void *func_02078058(void *ptr)
{
    func_020a88ec(ptr);
    *(unsigned int *) ptr = (unsigned int) &data_020e1870;
    return ptr;
}
