/* player_messages: 11 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020705a8 @ 0x020705a8, 0x18 bytes, Thumb
 * func_0207059c @ 0x0207059c, 0xc bytes, Thumb
 * func_02070590 @ 0x02070590, 0xc bytes, Thumb
 * func_0207055c @ 0x0207055c, 0x34 bytes, Thumb
 * func_02070500 @ 0x02070500, 0x5c bytes, Thumb
 * func_020704f4 @ 0x020704f4, 0xc bytes, Thumb
 * func_020704c0 @ 0x020704c0, 0x34 bytes, Thumb
 * func_02070490 @ 0x02070490, 0x30 bytes, Thumb
 * func_02070444 @ 0x02070444, 0x4a bytes, Thumb
 * func_02070438 @ 0x02070438, 0xc bytes, Thumb
 * func_0207042c @ 0x0207042c, 0xc bytes, Thumb
 */

extern void *func_02097f14(void *buffer);
extern void func_02066650(void *object);
extern int data_021f36ec;
extern unsigned char data_020df6a4;
extern void *data_020ccf94;
extern void func_02073820(void *);
extern void func_020737f0(void *, int *, int);
extern void func_02073770(void *, int, int);
extern void *func_020e9958(void *, unsigned int);
extern void MI_CpuCopy8(unsigned char *, const void *, unsigned int);
extern int func_020979f0(const void *, int);
extern int func_0209782c(void);
extern void func_020e993c(void *, const void *);
extern void *data_021fbe94;
extern void func_0206ea84(void *a, void *b);
extern void func_0206ea28(void);
extern void func_0207a500(void *a);
extern char data_021cfbbc;
extern char data_021f3b68;
extern char data_021e5a2c;
extern void func_0200467c(int cmd);
extern int func_0208b500(void);
extern void func_0208d0bc(int a, int b, int c);
extern int data_020df6a8[];
extern int func_0208d12c(void *);
extern void func_02045d98(unsigned char);

void func_020705a8(void *packet, int player)
{
    func_02066650(func_02097f14(&data_021f36ec));
}

unsigned char func_0207059c(void)
{
    return data_020df6a4;
}

void func_02070590(char r0)
{
    (*(char *) &data_020df6a4) = r0;
}

void func_0207055c(int a, int b)
{
    void *obj = data_020ccf94;
    func_02073820(obj);
    func_020737f0(obj, &a, 1);
    func_02073770(obj, 22, b);
}

void func_02070500(unsigned char *p, int q)
{
    void *heap;
    void *r;
    int err;

    heap = data_021fbe94;
    r = func_020e9958(heap, 0x100);
    err = 11;
    MI_CpuCopy8(p + 1, r, 0x100);
    if (func_020979f0(r, 1) != 0) {
        if (func_0209782c() != 0) {
            err = 9;
        } else {
            err = 10;
        }
    }
    func_020e993c(heap, r);
    func_0207055c(err, q);
}

void func_020704f4(unsigned char *arg0, int player)
{
    unsigned char value;

    value = *arg0;
    data_020df6a4 = value;
}

void func_020704c0(void *arg, int player)
{
    MI_CpuCopy8((unsigned char *) ((char *) arg + 1), (const void *) (&data_021cfbbc), 0x10);
    (((int) (func_0206ea84(&data_021f3b68, &data_021cfbbc), &data_021f3b68)), func_0206ea28());
    func_0207a500(&data_021e5a2c);
}

void func_02070490(int param)
{
    if (param == 0) {
        func_0200467c(0x67);
    } else {
        func_0200467c(0x66);
    }
    func_0208d0bc(func_0208b500(), data_020df6a8[param], 0);
}

void func_02070444(unsigned char *p, int player)
{
    int x;

    x = p[0] - 13;
    if (x == 0) {
        if (func_0208d12c((void *) func_0208b500()) != 0) {
            return;
        }
        func_02070490(x);
        func_0207055c(18, 4);
    } else {
        if (func_0208d12c((void *) func_0208b500()) == 0) {
            return;
        }
        func_02070490(x);
        x += 18;
        func_0207055c((unsigned char) x, 4);
    }
}

void func_02070438(unsigned char *data, int player)
{
    func_02070490(*data - 0x12);
}

void func_0207042c(unsigned char *p, int player)
{
    func_02045d98(p[1]);
}
