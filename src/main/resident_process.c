/* resident_process: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209da78 @ 0x0209da78, 0x58 bytes, Thumb
 * func_0209da30 @ 0x0209da30, 0x48 bytes, Thumb
 * func_0209da20 @ 0x0209da20, 0x10 bytes, Thumb
 * func_0209da1c @ 0x0209da1c, 0x4 bytes, Thumb
 * func_0209d9f4 @ 0x0209d9f4, 0x28 bytes, Thumb
 * func_0209d9d4 @ 0x0209d9d4, 0x20 bytes, Thumb
 */

extern void func_020b3bd4(void);
extern int func_02037c48(void);
extern void func_02053e7c(void);
extern void func_02062b04(void);
extern int func_02072260(void);
extern void func_02072338(int);
extern int func_0204d9d8(int x);
extern int func_0204e65c(int x);
extern int func_0204dea0(int x);
extern void func_02074d24(int x);
extern void func_020a6c94(void);
extern void func_02085e94(void);
extern int data_021dc740;
extern int data_021fbe94;
extern void func_020b3ba0(void);
extern int func_02037c28(void);
extern void func_02053e6c(void);
extern void func_02062af4(void);
extern void func_02072330(void *);
extern void func_0204d9ac(int);
extern void func_0204e624(int);
extern void func_0204de5c(int);
extern void func_02074944(void);
extern void func_020a6c90(void);
extern int func_020a536c(void);
extern void func_020ee62c(void *);
extern void func_020edf54(void *);
extern unsigned char data_020da13c[];
extern unsigned char data_020e360c[];

int func_0209da78(int param)
{
    data_021dc740 = param;
    func_020b3bd4();
    func_02037c48();
    func_02053e7c();
    func_02062b04();
    func_02072338((int) func_02072260());
    func_0204d9d8(data_021fbe94);
    func_0204e65c(data_021fbe94);
    func_0204dea0(data_021fbe94);
    func_02074d24(data_021fbe94);
    func_020a6c94();
    func_02085e94();
    return 1;
}

int func_0209da30(void)
{
    func_020b3ba0();
    func_02037c28();
    func_02053e6c();
    func_02062af4();
    func_02072330((void *) func_02072260());
    func_0204d9ac(data_021fbe94);
    func_0204e624(data_021fbe94);
    func_0204de5c(data_021fbe94);
    func_02074944();
    func_020a6c90();
    return 1;
}

int func_0209da20(void)
{
    func_020a536c();
    return 1;
}

int func_0209da1c(void)
{
    return 1;
}

volatile int *func_0209d9f4(volatile int *p)
{
    *p = (unsigned int) data_020e360c;
    *p = (unsigned int) data_020da13c;
    func_020ee62c((void *) p);
    func_020edf54((void *) p);
    return p;
}

void *func_0209d9d4(void *self)
{
    volatile unsigned int *p;
    p = (volatile unsigned int *) self;
    *p = (unsigned int) ((char *) data_020e360c);
    *p = (unsigned int) ((char *) data_020da13c);
    func_020ee62c(self);
    return self;
}
