/* func_02031e90 @ 0x02031e90, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020edb3c(void *ptr);

extern unsigned char data_020da1fc[];

void *func_02031e90(void *ptr)
{
    *(void **) ptr = (void *) data_020da1fc;
    func_020edb3c(ptr);
    return ptr;
}
