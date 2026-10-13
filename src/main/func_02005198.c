/* func_02005198 @ 0x02005198, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f5914(void *);

extern unsigned char data_020d8414[];

void *func_02005198(void *ptr)
{
    *(void **) ptr = (void *) data_020d8414;
    func_020f5914(ptr);
    return ptr;
}
