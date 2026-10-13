/* func_0206f49c @ 0x0206f49c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ee62c(void *);

extern unsigned char data_020da13c[];
extern unsigned char data_020df548[];

void *func_0206f49c(void *ptr)
{
    volatile void **p = (volatile void **) ptr;
    *p = (void *) data_020df548;
    *p = (void *) data_020da13c;
    func_020ee62c(ptr);
    return ptr;
}
