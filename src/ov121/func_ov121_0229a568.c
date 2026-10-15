/* func_ov121_0229a568 @ 0x0229a568, 0x60 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02208c58(unsigned char *p1, unsigned char *p2, int n);
extern int func_ov121_0229af58(unsigned char *s, unsigned char c);
extern int func_ov121_0229af40(unsigned char *s, unsigned char c);
extern void func_ov002_02209908(unsigned char *p, int a, int b);
extern void func_ov002_0220970c(unsigned char *p, int n);
extern unsigned char *func_ov002_02208098(unsigned char *s, unsigned char value);

void func_ov121_0229a568(unsigned char *s)
{
    int a;
    int b;
    func_ov002_02208c58(s + 0x528, s + 0x910, 0);
    a = func_ov121_0229af58(s, s[0xaf]) - 0x18;
    b = func_ov121_0229af40(s, s[0xaf]) + 0x10;
    func_ov002_02209908(s + 0x528, a, b);
    func_ov002_0220970c(s + 0x528, 0);
    func_ov002_02208098(s, 0xe);
}
