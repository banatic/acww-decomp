/* func_0205bb48 @ 0x0205bb48, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205bbe8(void *ptr);
extern int data_020dd3a4;

void *func_0205bb48(void *ptr)
{
    func_0205bbe8(ptr);
    *(void **) ptr = (void *) &data_020dd3a4;
    return ptr;
}
