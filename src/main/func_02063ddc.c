/* func_02063ddc @ 0x02063ddc, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02063e80(void *ptr);
extern unsigned int data_020de64c;

void *func_02063ddc(void *ptr)
{
    unsigned int *p = (unsigned int *) ptr;
    p[0] = (unsigned int) &data_020de64c;
    func_02063e80(ptr);
    return ptr;
}
