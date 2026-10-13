/* func_0200956c @ 0x0200956c, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0200f290(void *, int);
extern void func_020109fc(void *, int, int, int);
extern void func_020095ac(void *, int);
extern void func_0200f27c(void *, int);

void func_0200956c(void *a, void *b)
{
    signed short *s;
    char *p;

    s = (signed short *) ((char *) b + 12);
    p = (char *) a + 0x7D4;
    if (func_0200f290(a, 0x17) == 0) {
        func_020109fc(a, 1, 3, 0);
    }
    func_020095ac(p, *s);
    func_0200f27c(a, 6);
}
