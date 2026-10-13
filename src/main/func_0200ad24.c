/* func_0200ad24 @ 0x0200ad24, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Pair {
    int a;
    int b;
} Pair;

extern void func_0200e92c(char *);
extern void func_0200e90c(char *, int, int, int);
extern void func_0200ad78(char *, Pair *, unsigned int, int);
extern int func_0200e894(int, char *);
extern void func_0200e91c(char *);

int func_0200ad24(int a, Pair *p, int c, int d, short e)
{
    Pair tmp;
    char obj[12];
    char out[16];
    int result;

    func_0200e92c(obj);
    func_0200e90c(obj, 0x1a, d, e);

    tmp.a = p->a;
    tmp.b = p->b;

    func_0200ad78(out, &tmp, 0x0000fff1, c);

    result = func_0200e894(a, obj);
    func_0200e91c(obj);

    return result;
}
