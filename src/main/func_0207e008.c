/* func_0207e008 @ 0x0207e008, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern void *func_02099870(int);
extern int func_020807a8(int, void *);
extern unsigned int func_02081a88(int);
extern void func_020b4a20(int, void *, void *);
extern char data_020e195c[];

void func_0207e008(int a, int b, int c)
{
    int v;
    void *p;
    unsigned int t;
    char local;

    if (c == 0) {
        c = func_020984e8();
    }

    v = 0;
    if (c != 0) {
        p = func_02099870(c);
        v = func_020807a8(a, p);
    }

    if (v) {
        t = func_02081a88(v);
        if (t < 0x58) {
            local = (char) t;
            func_020b4a20(b, &local, data_020e195c);
        }
    }
}
