/* func_020b3818 @ 0x020b3818, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b38a0(void *);
extern void func_020b39b4(void *);

void *func_020b3818(void *arg)
{
    void *p = arg;

    func_020b38a0((char *) p + 4);
    func_020b39b4(p);
    return p;
}
