/* func_02046a74 @ 0x02046a74, 0x154 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int unk_00;
    unsigned int w1;
} Pair;
typedef struct {
    unsigned char b[4];
} Trio;
struct St {
    char data[20];
};
extern unsigned char data_021f39fc[];
extern char data_021c779c[];
extern char data_021dc7a8[];
extern char data_021f3b0c[];
extern void func_0209e474(void *p);
extern int func_0209e350(void *dst, void *src);
extern void func_02046bc8(void);
extern int func_020b6660(void);
extern int func_020b6640(void);
extern void func_02040c80(void);
extern void func_02042500(void);
extern int func_020c15bc(void);
extern void func_0209fa40(char *p);
extern void func_02046bf4(void *a, void *b, int c, int d, int e);
extern void func_0209e100(void *p, int n);
extern void func_0204763c(char *p, int n);
extern void func_02046c2c(char *p);
extern void func_0204cc34(char *p, void *q);
extern void func_0205ba64(void *p);
extern void func_0205b8e0(void *p);
extern void func_0205ba60(void *p);
extern void func_020873b4(char *p, int n);
extern void func_020991d4(void);
void func_02046a74(int param)
{
    Pair a;
    Pair b;
    Trio c;
    char (*val)[];
    struct St st;
    unsigned char *g;
    int t;
    int days;
    a.unk_00 = 0;
    a.w1 = 0;
    b.unk_00 = 0;
    b.w1 = 0;
    func_0209e474(&a);
    val = &data_021dc7a8;
    g = data_021f39fc;
    b.unk_00 = 0;
    b.w1 = 0;
    ((unsigned char *) (&b))[5] = g[2];
    ((unsigned char *) (&b))[4] = g[1];
    ((unsigned char *) (&b))[3] = g[0];
    ((unsigned char *) (&b))[2] = 6;
    t = func_0209e350(&b, &a);
    days = t / 0x3c / 0x18;
    func_02046bc8();
    if ((days >= 1) && (param == 0)) {
        if ((func_020b6660() != 0) || (func_020b6640() != 0)) {
            func_02040c80();
        }
    }
    func_02042500();
    if (days >= 1) {
        t = func_020c15bc();
        if (param == 0) {
            if ((func_020b6660() != 0) || (func_020b6640() != 0)) {
                func_0209fa40((char *) (((int) (*val)) + 0x173dd));
            }
        }
        if (((param != 0) || (func_020b6660() != 0)) || (func_020b6640() != 0)) {
            func_02046bf4(&b, &a, days, t, param);
            func_0209e100(&a, 6);
            g[2] = ((unsigned char *) (&a))[5];
            g[1] = ((unsigned char *) (&a))[4];
            g[0] = ((unsigned char *) (&a))[3];
        }
    } else {
        if (param != 0) {
            func_0204763c(data_021c779c, 1);
        }
        if (t < 0) {
            c.b[2] = ((unsigned char *) (&a))[5];
            c.b[1] = ((unsigned char *) (&a))[4];
            c.b[0] = ((unsigned char *) (&a))[3];
            func_02046c2c(data_021c779c);
            func_0204cc34((char *) (((int) (*val)) + 0x17254), &c);
            func_0205ba64(&st);
            func_0205b8e0(&st);
            func_0205ba60(&st);
        }
        func_0209e100(&a, 6);
        g[2] = ((unsigned char *) (&a))[5];
        g[1] = ((unsigned char *) (&a))[4];
        g[0] = ((unsigned char *) (&a))[3];
    }
    func_020873b4(data_021f3b0c, days);
    func_020991d4();
}
