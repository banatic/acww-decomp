/* glasses_look: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0205de24 @ 0x0205de24, 0x4c bytes, Thumb
 * func_0205de10 @ 0x0205de10, 0x14 bytes, Thumb
 * func_0205ddfc @ 0x0205ddfc, 0x14 bytes, Thumb
 * func_0205dde8 @ 0x0205dde8, 0x14 bytes, Thumb
 * func_0205ddd4 @ 0x0205ddd4, 0x14 bytes, Thumb
 * func_0205ddc0 @ 0x0205ddc0, 0x14 bytes, Thumb
 */

extern int func_021077e8(int x);
extern int func_020b9eec(void *obj, int val, int flag);
extern unsigned long func_0205df4c(unsigned int, unsigned char);
extern unsigned char data_021c9e68[];
extern int func_0205df40(void *p, unsigned char c);
extern int func_0205df34(unsigned char *param1, unsigned char param2);
extern int func_0205df2c(void *ptr, unsigned char byte);
extern void func_0205df24(unsigned char *a, unsigned char b, int c);

unsigned long func_0205de10(unsigned char *arg);
int func_0205dde8(unsigned char *ptr);

int func_0205de24(void *self)
{
    void *obj;
    unsigned char b;
    unsigned int f1;
    unsigned int f2;

    obj = (void *) func_0205dde8(self);
    b = ((unsigned char *) obj)[0xd];
    f1 = (b == 2) ? 1 : 0;
    if (f1) {
        return 1;
    }
    f2 = (b == 1) ? 1 : 0;
    if (f2 == 0) {
        func_020b9eec(obj, func_021077e8((int) func_0205de10((unsigned char *) self)), 1);
    }
    return 0;
}

unsigned long func_0205de10(unsigned char *arg)
{
    return func_0205df4c((unsigned int) data_021c9e68, *arg);
}

int func_0205ddfc(unsigned char *ptr)
{
    return func_0205df40(((int *) data_021c9e68), *ptr);
}

int func_0205dde8(unsigned char *ptr)
{
    return func_0205df34(((unsigned char *) data_021c9e68), *ptr);
}

int func_0205ddd4(unsigned char *p)
{
    return func_0205df2c((void *) data_021c9e68, *p);
}

void func_0205ddc0(unsigned char *a, int b)
{
    func_0205df24(((unsigned char *) data_021c9e68), *a, b);
}
