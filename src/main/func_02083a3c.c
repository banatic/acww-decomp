/* func_02083a3c @ 0x02083a3c, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02078a70(void *ptr, int);

void func_02083a3c(void *arg, int argument1)
{
    unsigned char *p = (unsigned char *) arg;
    func_02078a70(p + 4, (int) argument1);
    *p = 1;
}
