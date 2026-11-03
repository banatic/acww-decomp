/* field_actor_states_21: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0200c3b0 @ 0x0200c3b0, 0x40 bytes, Thumb
 * func_0200c37c @ 0x0200c37c, 0x34 bytes, Thumb
 * func_0200c368 @ 0x0200c368, 0x14 bytes, Thumb
 * func_0200c33c @ 0x0200c33c, 0x2c bytes, Thumb
 */

struct Struct0200c37c {
    char pad_00[0xC];
    unsigned short unk_0C;
};

extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern void func_0200c3f0(void *, int);
extern int func_0200e894(void *, void *);
extern int func_0200e91c(void *);
extern int func_0200f290(void *param0, int param1);
extern void func_020109fc(void *param0, int param1, unsigned short param2, int param3);
extern void func_0200eebc(void *param0);
extern void func_0200f268(void *param0, int param1);
extern void func_02010f5c(int);
extern int func_02056f94(int);

int func_0200c3b0(void *p1, int p2, int p3, int p4)
{
    char a[0xc];
    char b[0x10];
    int ret;

    func_0200e92c(a);
    func_0200e90c(a, 0x10, p3, p4);
    func_0200c3f0(b, p2);
    ret = func_0200e894(p1, a);
    func_0200e91c(a);
    return ret;
}

void func_0200c37c(void *arg0, struct Struct0200c37c *arg1, int previous)
{
    unsigned short field;
    field = arg1->unk_0C;
    if (func_0200f290(arg0, 23) == 0) {
        func_020109fc(arg0, 0, field, 0);
    }
    func_0200eebc(arg0);
    func_0200f268(arg0, 29);
}

void func_0200c368(int a, int b)
{
    func_0200c3b0((void *) a, 3, 5, b);
}

void func_0200c33c(int param)
{
    func_02010f5c(param);
    if (func_02056f94(param + 0x2d0)) {
        func_020109fc((void *) param, 0, 3, 0);
    }
}
