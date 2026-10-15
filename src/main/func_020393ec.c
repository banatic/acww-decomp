/* func_020393ec @ 0x020393ec, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203931c(void *);

extern unsigned char data_021c6738[];

void func_020393ec(unsigned int *ptr)
{

    func_0203931c(ptr);
    ptr = (unsigned int *) data_021c6738;
    *ptr = 0;
}
