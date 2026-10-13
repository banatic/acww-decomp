/* func_0209b8a4 @ 0x0209b8a4, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209b870(void *);

void func_0209b8a4(void *arg0, unsigned char arg1)
{
    unsigned char *ptr;

    func_0209b870(arg0);
    ptr = (unsigned char *) arg0 + 0x2f;
    *ptr = arg1;
}
