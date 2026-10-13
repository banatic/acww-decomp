/* func_0200a300 @ 0x0200a300, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200e92c(void *ptr);
extern void func_0200e90c(void *ptr, int a, int b, int c);
extern int func_0200e894(void *a, void *b);
extern void func_0200e91c(void *ptr);

int func_0200a300(void *arg0, int arg1, int arg2)
{
    unsigned char local[0x20];
    int result;

    func_0200e92c(local);
    func_0200e90c(local, 0x31, arg1, arg2);
    result = func_0200e894(arg0, local);
    func_0200e91c(local);
    return result;
}
