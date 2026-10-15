/* func_0203a3cc @ 0x0203a3cc, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a8c38(void *ptr);
extern void func_020edb3c(void *ptr);

extern unsigned char data_020da640[];

void *func_0203a3cc(void *ptr)
{
    *(void **) ptr = (void *) data_020da640;
    func_020a8c38(ptr);
    func_020edb3c(ptr);
    return ptr;
}
