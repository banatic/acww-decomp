/* func_020b33e0 @ 0x020b33e0, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b3740(void *);
extern void func_020b3650(void *);
extern void *func_020b356c(void *);
extern void func_020b35e0(void *);

void *func_020b33e0(void *base)
{
    func_020b3740(base);
    func_020b3650((char *) base + 0x14);
    func_020b356c((char *) base + 0x18);
    func_020b35e0((char *) base + 0x34);
    return base;
}
