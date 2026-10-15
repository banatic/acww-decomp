/* func_ov144_0229a588 @ 0x0229a588, 0x34 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220b9b8(void *a, void *b, int c, int d);
extern unsigned char *func_ov002_02208098(void *a, unsigned char value);
extern void func_0208e5c4(void *a);

void func_ov144_0229a588(void *a, char b)
{
    char c;
    void *p;
    c = b;
    p = (char *) a + 0x750;
    func_ov002_0220b9b8(p, &c, 1, 0);
    func_ov002_02208098(a, 0xc);
    func_0208e5c4((char *) a + 0xc4);
}
