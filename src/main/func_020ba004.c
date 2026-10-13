/* func_020ba004 @ 0x020ba004, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ba1bc(void *ptr);
extern void func_020ba1b0(void *ptr);

void func_020ba004(void *ptr)
{
    void *p;
    p = ptr;
    func_020ba1bc(p);
    p = (char *) p + 0x10;
    func_020ba1b0(p);
}
