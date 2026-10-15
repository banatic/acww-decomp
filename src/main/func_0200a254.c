/* func_0200a254 @ 0x0200a254, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern int func_0200e894(int, void *);
extern int func_0200e91c(void *);

int func_0200a254(int arg0, int arg1, int arg2)
{
    char buf[0x20];
    int ret;

    func_0200e92c(buf);
    func_0200e90c(buf, 0x32, arg1, arg2);
    ret = func_0200e894(arg0, buf);
    func_0200e91c(buf);
    return ret;
}
