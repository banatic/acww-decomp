/* func_0201404c @ 0x0201404c, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02014718(void);

void func_0201404c(void *arg0)
{
    unsigned char *ptr = (unsigned char *) arg0;
    func_02014718();
    ptr[0xa] = 1;
}
