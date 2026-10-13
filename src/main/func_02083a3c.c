/* func_02083a3c @ 0x02083a3c, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02078a70(void *ptr);

void func_02083a3c(void *arg)
{
    unsigned char *p = (unsigned char *) arg;
    func_02078a70(p + 4);
    *p = 1;
}
