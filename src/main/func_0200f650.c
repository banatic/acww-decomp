/* func_0200f650 @ 0x0200f650, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200f6bc(int *dst, int src, int *args);
extern int func_020e8bb0(void *dst, int src, int size, int flags, int control);

void func_0200f650(int a0, int a1)
{
    int buf[3];
    func_0200f6bc(buf, a0, &a1);
    func_020e8bb0((char *) a0 + 0x824, buf[0], 0x800, 0x2000, 0x333);
    func_020e8bb0((char *) a0 + 0x828, buf[1], 0x800, 0x2000, 0x333);
    func_020e8bb0((char *) a0 + 0x82c, buf[2], 0x800, 0x2000, 0x333);
}
