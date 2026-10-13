/* func_0209b604 @ 0x0209b604, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209c398(void *ptr);
extern void func_0209baf4(void *ptr);

void func_0209b604(void *arg)
{
    void *ptr;
    void *ptr2;

    ptr = arg;
    func_0209c398(ptr);
    ptr2 = (char *) ptr + 0x24;
    func_0209baf4(ptr2);
}
