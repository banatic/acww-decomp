/* func_02099e40 @ 0x02099e40, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02003750(void *ptr);
extern void func_020642f8(void *ptr);

void *func_02099e40(void *ptr)
{
    func_02003750((char *) ptr + 0xe);
    func_020642f8(ptr);
    return ptr;
}
