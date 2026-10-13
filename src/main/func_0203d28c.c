/* func_0203d28c @ 0x0203d28c, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203d368(void *);

void func_0203d28c(void *arg0)
{
    unsigned char *p = (unsigned char *) arg0;

    func_0203d368(arg0);
    p[1] &= ~1;
    p[1] &= ~2;
    p[1] &= ~4;
}
