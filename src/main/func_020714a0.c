/* func_020714a0 @ 0x020714a0, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02071aa8(unsigned int a, unsigned char b, unsigned int c, unsigned char d, int x);
extern int func_02071d8c(unsigned int a, unsigned char b, unsigned int c, unsigned char d, int x);

typedef struct {
    unsigned int a : 4;
    unsigned int b : 10;
    unsigned int c : 4;
    unsigned int d : 10;
    unsigned int e : 1;
} Flags;

int func_020714a0(Flags *p)
{
    unsigned int a = p->a;
    unsigned char b = p->b;
    unsigned int c = p->c;
    unsigned char d = p->d;
    unsigned int e = p->e;
    if (e != 0) {
        return func_02071aa8(a, b, c, d, 0);
    } else {
        return func_02071d8c(a, b, c, d, 0);
    }
}
