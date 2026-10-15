/* func_020356c4 @ 0x020356c4, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020374d0(void *p, int a, int b, int c, int w, int value);
extern void func_02035198(unsigned int val, void *p);
extern void func_020374cc(void *p);
extern unsigned int data_021c526c;

void func_020356c4(int a, int b, int c, int d)
{
    unsigned char buf[32];

    func_020374d0(buf, a, b, c, 0, d);
    func_02035198(data_021c526c, buf);
    func_020374cc(buf);
}
