/* func_02085350 @ 0x02085350, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02085310(void *a, char *b);
extern void *func_0207b9d0(char *p);
extern void func_020794c0(void *p, int x);
extern void func_020794a4(void *p, int x);

void func_02085350(void *a, char *b)
{
    void *r;

    func_02085310(a, b);
    r = func_0207b9d0(b - 12);
    if (r != 0) {
        func_020794c0(r, 0);
        func_020794a4(r, 0);
    }
}
