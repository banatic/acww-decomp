/* func_0203564c @ 0x0203564c, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020374d0(void *dest, int a, int b, int c, int d, int e);
extern void func_02035198(int a, void *b);
extern void func_020374cc(void *b);
extern int data_021c526c;

void func_0203564c(int a, int b)
{
    unsigned char buf[0x1c];
    func_020374d0(buf, a, b, 0x7f, 0, 0);
    buf[0x11] = 1;
    func_02035198(data_021c526c, buf);
    func_020374cc(buf);
}
