/* func_02079e64 @ 0x02079e64, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020984e8(void);
extern int func_02099020(void *, int);
extern char *func_02079350(void);
extern void *func_0208150c(char *);
extern int func_02003704(void *);
extern void *func_020036e8(void *);
extern int func_020821d4(void *, void *);
extern void func_020794d4(char *, int);
extern void func_02079540(char *, int);

void func_02079e64(void *a, char *b, void *c)
{
    void *h;
    int v;
    int flag;
    char *q;
    void *x;
    int i;
    int zero;

    h = func_020984e8();
    if (h != 0) {
        v = func_02099020(h, 1);
    } else {
        v = 0;
    }
    flag = (v != 0) ? 1 : 0;
    q = func_02079350();
    i = 0;
    zero = 0;
    for (; i < 8; i++) {
        x = func_0208150c(b);
        if (func_02003704(x) != 0) {
            if (flag == 0) {
                if (func_020821d4(func_020036e8(x), c) != 0) {
                    func_020794d4(q, 2);
                    func_02079540(q, zero);
                }
            }
        } else {
            func_020794d4(q, 3);
            func_02079540(q, 7);
        }
        b += 0x7ec;
        q += 0x2c;
    }
}
