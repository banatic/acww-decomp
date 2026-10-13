/* func_020970cc @ 0x020970cc, 0xbc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f43ec;
extern void func_02066694(void *);
extern void func_02066650(void *);
extern void func_020984e8(void);
extern int func_02099870(void);
extern unsigned char func_02096ebc(int);
extern unsigned char func_0209767c(int, int);
extern int func_020970a4(int);
extern void func_02066024(void *, void *, int, void *, void *, int);
extern int func_02096ee4(int);
extern void func_02065ed0(void *, int, int);
extern int func_02097a54(void *);
extern void func_02066688(void *);
extern int func_020979f0(void *, int);

int func_020970cc(int a, int b)
{
    unsigned char data[3];
    struct {
        unsigned int pad[64];
    } ctx;
    int x;
    int v;
    int r4;

    func_02066694(&ctx);
    func_02066650(&ctx);
    func_020984e8();
    r4 = func_02099870();

    data[0] = data_021f43ec;
    data[0] = func_02096ebc(a);
    data[1] = 1;
    if (a == 0x1a) {
        data[1] = 0x12;
    }
    data[2] = func_0209767c(3, b);

    x = func_020970a4(a);
    func_02066024(&ctx, data, x, &data[1], &data[2], r4);

    v = func_02096ee4(a);
    if (v != 0xfff1) {
        func_02065ed0(&ctx, v, 1);
    }

    if (func_02097a54(&ctx) != 0) {
        func_02066688(&ctx);
        return 1;
    }
    if (func_020979f0(&ctx, 0) != 0) {
        func_02066688(&ctx);
        return 1;
    }
    func_02066688(&ctx);
    return 0;
}
