/* func_0203df94 @ 0x0203df94, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020682e0(unsigned int heap_id);
extern void *func_02068340(void *heap, unsigned int size);

void *func_0203df94(unsigned int size)
{
    return func_02068340(func_020682e0(0), size);
}
