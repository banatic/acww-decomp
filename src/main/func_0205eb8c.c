/* func_0205eb8c @ 0x0205eb8c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205ebb4(void);
extern int func_0205ec50(void *a, int b, int c, void *d, int e, int f);

void func_0205eb8c(void *a, void *b, int c)
{
    unsigned char d;
    void *e;
    int f;

    d = *(unsigned char *) a;
    func_0205ebb4();
    f = c;
    e = b;
    func_0205ec50(a, d, 0, e, f, 0);
}
