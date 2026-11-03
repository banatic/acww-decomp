/* spawner: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02083da4 @ 0x02083da4, 0x26 bytes, Thumb
 * func_02083d78 @ 0x02083d78, 0x2c bytes, Thumb
 * func_02083d54 @ 0x02083d54, 0x22 bytes, Thumb
 * func_02083d1c @ 0x02083d1c, 0x38 bytes, Thumb
 * func_02083cec @ 0x02083cec, 0x30 bytes, Thumb
 * func_02083cc0 @ 0x02083cc0, 0x2c bytes, Thumb
 */

struct UnkStruct_02083cc0 {
    void *vtable;
    char pad_04[0x4c];
    char sub;
};

extern int func_0208602c(void);
extern int func_020860c0(int);
extern void func_02087e4c(int, int);
extern int func_02087de8(int);
extern int func_020860b8(int);
extern int func_02087854(int, int);
extern int func_020644cc(int) __attribute__((arm));
extern int func_020860bc(int x);
extern void func_02087a78(int a, int b, int c, int d);
extern void func_0204f7e0(int a, void *p);
extern void func_02084f84(void *);
extern void func_020ee62c(void *);
extern void func_020edf54(void *);
extern unsigned char data_020da13c[];
extern unsigned char data_020e1cc0[];

int func_02083da4(int param0, int param1, int param2)
{
    int res;
    res = func_020860c0((int) func_0208602c());
    func_02087e4c(res, param1);
    *(unsigned short *) (param2 + 2) = (unsigned short) func_02087de8(res);
    return 1;
}

int func_02083d78(int a, int b, unsigned short *out)
{
    int x;
    int y;
    x = func_0208602c();
    y = func_020860b8(x);
    func_02087854(y, b);
    out[1] = (unsigned short) func_020644cc(0xffff);
    return 1;
}

int func_02083d54(int a, int b, int c, int d)
{
    func_02087a78(func_020860bc(func_0208602c()), b, c + 2, d);
    return 1;
}

int func_02083d1c(int a, int b, unsigned short *c, int *d)
{
    struct {
        int x;
        int y;
        int z;
    } local;
    int t = d[2] + 0x6000;

    local.x = d[0] - 0x4000;
    local.y = 0;
    local.z = t;
    func_0204f7e0(b, &local);
    c[1] = 0;
    return 1;
}

void *func_02083cec(void *obj)
{
    *(void **) obj = (void *) data_020e1cc0;
    func_02084f84((char *) obj + 0x50);
    *(void **) obj = (void *) data_020da13c;
    func_020ee62c(obj);
    func_020edf54(obj);
    return obj;
}

struct UnkStruct_02083cc0 *func_02083cc0(struct UnkStruct_02083cc0 *self)
{
    self->vtable = ((char *) data_020e1cc0);
    func_02084f84((void *) (&self->sub));
    self->vtable = ((char *) data_020da13c);
    func_020ee62c(self);
    return self;
}
