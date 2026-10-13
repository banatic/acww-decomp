/* func_020aaa74 @ 0x020aaa74, 0x46 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020abd44(int);
extern int func_020abd2c(int);
extern int func_020a80c4(int, int, int, int);
extern void func_020a806c(int *, int *);

struct func_020aaa74_s {
    int a;
    char pad_04[12];
    int b;
};

int func_020aaa74(struct func_020aaa74_s *p)
{
    int r = 0;
    int v;
    int w;
    int t0;
    int t1;

    v = func_020abd44(p->a);
    w = func_020abd2c(p->a);
    if (func_020a80c4(v - 5, v + 0x15, w, w + 0x10)) {
        func_020a806c(&t0, &t1);
        p->b = t1 - w;
        r = 1;
    }
    return r;
}
