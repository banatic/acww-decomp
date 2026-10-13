/* func_02060480 @ 0x02060480, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02034270(void *dst, const void *src, int a, int b);
extern void func_0203423c(void *ptr);

void func_02060480(void *arg)
{
    unsigned char buf[0x40];
    unsigned int *p;
    unsigned int v;

    func_02034270(buf, (char *) arg + 8, 1, 1);
    p = (unsigned int *) (buf + 0x30);
    if (*p != 0) {
        v = *(unsigned int *) (buf + 0x3c);
        *(unsigned int *) ((char *) arg + 0xc) = v + 0xcd;
    }
    func_0203423c(buf);
}
