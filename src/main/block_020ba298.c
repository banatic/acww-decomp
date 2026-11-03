/* block_020ba298: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020ba334 @ 0x020ba334, 0xc bytes, Thumb
 * func_020ba31c @ 0x020ba31c, 0x18 bytes, Thumb
 * func_020ba310 @ 0x020ba310, 0xc bytes, Thumb
 * func_020ba2ec @ 0x020ba2ec, 0x24 bytes, Thumb
 * func_020ba2e0 @ 0x020ba2e0, 0xc bytes, Thumb
 * func_020ba2b8 @ 0x020ba2b8, 0x28 bytes, Thumb
 * func_020ba298 @ 0x020ba298, 0x20 bytes, Thumb
 */

extern unsigned char data_021fbb08[];
extern unsigned char data_021fba88[0x11];
extern int func_020984e8(void);
extern void func_02098ff8(int a, int b);
extern void func_020bc514(int *p);
extern int data_021f8b48;
extern unsigned char data_021fba68[];
extern void func_020ee62c(void *);
extern void func_020edf54(void *);
extern unsigned char data_020da13c[];
extern unsigned char data_020e69a4[];

void func_020ba334(void)
{
    data_021fbb08[6] = 1;
}

void func_020ba31c(int arg)
{
    if (arg) {
        data_021fbb08[8] = 1;
    } else {
        data_021fbb08[7] = 1;
    }
}

unsigned char func_020ba310(void)
{
    return data_021fba88[0x10];
}

void func_020ba2ec(void)
{
    int ret;
    ret = func_020984e8();
    if (ret) {
        func_02098ff8(ret, 0x32);
        func_020bc514(&data_021f8b48);
    }
}

void func_020ba2e0(void)
{
    data_021fba68[9] = 1;
}

void *func_020ba2b8(void *obj)
{
    *(volatile int *) obj = (int) ((int *) data_020e69a4);
    *(volatile int *) obj = (int) ((int *) data_020da13c);
    func_020ee62c(obj);
    func_020edf54(obj);
    return obj;
}

void *func_020ba298(void *arg)
{
    volatile unsigned int *ptr;
    ptr = (volatile unsigned int *) arg;
    *ptr = (unsigned int) data_020e69a4;
    *ptr = (unsigned int) data_020da13c;
    func_020ee62c(arg);
    return arg;
}
