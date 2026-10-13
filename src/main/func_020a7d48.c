/* func_020a7d48 @ 0x020a7d48, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a941c(void *ptr);

extern unsigned char data_020e3e44[];
extern unsigned char data_020e3e68[];

void *func_020a7d48(void *ptr)
{
    *(unsigned int *) ptr = (unsigned int) data_020e3e44;
    *(unsigned int *) ptr = (unsigned int) data_020e3e68;
    func_020a941c(ptr);
    return ptr;
}
