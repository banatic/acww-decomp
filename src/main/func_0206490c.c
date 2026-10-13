/* func_0206490c @ 0x0206490c, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02064300(void *, int, int, void *);
extern void func_02064af4(void *, void *, void *);

void func_0206490c(void *a, void *b, int c)
{
    char buf[0x80];
    func_02064300(buf, 0x80, c, (void *) (((unsigned int) (char *) &c & ~3) + 4));
    func_02064af4(buf, a, b);
}
