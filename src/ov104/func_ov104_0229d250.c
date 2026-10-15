/* func_ov104_0229d250 @ 0x0229d250, 0x64 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_022090e4(unsigned char *, int);
extern int func_ov002_02208ae4(unsigned char *);
extern int func_ov002_02208ad8(unsigned char *, unsigned char);
extern void func_ov002_0220a0b4(unsigned char *, int, int);
extern void func_0208e4c0(unsigned char *, int);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov104_0229d250(unsigned char *p)
{
    int a;
    int b;

    p[0xBC] = 4;
    p[0xBD] = func_ov002_022090e4(p + 0x2504, 1);
    a = func_ov002_02208ae4(p + 0x2504);
    b = func_ov002_02208ad8(p + 0x2504, p[0xBD]);
    func_ov002_0220a0b4(p + 0x24A0, a, b);
    func_0208e4c0(p + 0x24A0, 8);
    func_ov002_02208098((void *) (p), 23);
}
