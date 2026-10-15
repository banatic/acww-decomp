/* func_02033100 @ 0x02033100, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02030690(void *);
extern void func_020342a4(void *);

void *func_02033100(void *ptr)
{
    func_02030690(ptr);
    func_020342a4((char *) ptr + 0x14);
    return ptr;
}
