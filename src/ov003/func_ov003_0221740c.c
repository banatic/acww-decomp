/* func_ov003_0221740c @ 0x0221740c, 0x34 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_020109a0(void *p, int b, int c, unsigned short d);
extern void func_ov003_02217440(void *p);
extern int func_0200f328(void *p, int a);
extern unsigned int *func_0200f27c(void *p, int a);

void func_ov003_0221740c(void *p, void *message, int previous)
{
    func_020109a0(p, 0x63, 3, 0);
    func_ov003_02217440((char *) p + 0x7d4);
    func_0200f328(p, 0x856);
    func_0200f27c(p, 9);
}
