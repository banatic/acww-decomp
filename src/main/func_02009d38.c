/* func_02009d38 @ 0x02009d38, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern int func_0200e894(int, void *);
extern int func_0200e91c(void *);

int func_02009d38(int arg0, unsigned short arg1, int arg2, int arg3)
{
    unsigned char buf[0x1C];
    int result;

    func_0200e92c(buf);
    func_0200e90c(buf, 0x3f, arg2, arg3);
    *(unsigned short *) (buf + 0xC) = arg1;
    result = func_0200e894(arg0, buf);
    func_0200e91c(buf);
    return result;
}
