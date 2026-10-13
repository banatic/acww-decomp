/* func_0200a3ac @ 0x0200a3ac, 0x9c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02057d58(char *p, unsigned int a, unsigned char b, unsigned int c, char *d, unsigned int e);
extern void func_020109a0(char *p, unsigned int a, unsigned int b, unsigned int c);
extern void func_02057d0c(unsigned int a, char *p);
extern void func_0200f328(char *p, unsigned int a);

void func_0200a3ac(char *a, char *b)
{
    char *p = b + 0xc;
    func_02057d58(a + 0x820, *(unsigned int *) (b + 0xc), *(unsigned char *) (p + 4), *(unsigned int *) (p + 8), a,
                  *(unsigned int *) (p + 0xc));
    func_020109a0(a, 0x28, 3, 0);
    func_02057d0c(1, a);
    func_0200f328(a, 0x4f);
    {
        unsigned short v = *(unsigned short *) (a + 0x820);
        if (v == 0x1373 || v == 0x1375 || v == 0x1377 || v == 0x1379 || v == 0x136a || v == 0x137b) {
            *(char *) (a + 0x8eb) = -1;
        } else {
            *(char *) (a + 0x8eb) = 0;
        }
    }
}
