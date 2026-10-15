/* func_02038d18 @ 0x02038d18, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020da530;
extern void *func_020a8c38(void *);

void *func_02038d18(void *ptr)
{
    *(unsigned int *) ptr = (unsigned int) &data_020da530;
    func_020a8c38(ptr);
    return ptr;
}
