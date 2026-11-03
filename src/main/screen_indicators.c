/* screen_indicators: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208b01c @ 0x0208b01c, 0x18 bytes, Thumb
 * func_0208affc @ 0x0208affc, 0x20 bytes, Thumb
 * func_0208afdc @ 0x0208afdc, 0x20 bytes, Thumb
 * func_0208afb4 @ 0x0208afb4, 0x28 bytes, Thumb
 * func_0208af98 @ 0x0208af98, 0x1c bytes, Thumb
 * func_0208af7c @ 0x0208af7c, 0x1c bytes, Thumb
 * func_0208af60 @ 0x0208af60, 0x1c bytes, Thumb
 * func_0208af44 @ 0x0208af44, 0x1c bytes, Thumb
 */

extern void *func_020edf70(unsigned int);
extern void *func_020ee660(void *p);
extern unsigned char data_020da13c[];
extern unsigned char data_020e2288[];
extern void func_020ee62c(void *p);
extern void func_020edf54(void *object);
extern void func_02003df0(void);
extern void func_02003a64(void);
extern void func_0208ee14(void);
extern void func_0208b55c(void);
extern void func_0208b54c(void);
extern void func_0208ee10(void);
extern void func_02003a54(void);
extern void func_02003de0(void);
extern void func_02003dd0(void);
extern void func_02003a44(void);
extern void func_0208ee00(void);
extern void func_0208b53c(void);
extern void func_02003a34(void);
extern void func_02003dc0(void);
extern void func_0208b52c(void);
extern void func_0208edf0(void);

void *func_0208affc(void *p);

void func_0208b01c(void)
{
    unsigned int r0;
    void *ptr;

    r0 = (unsigned int) func_020edf70(0x50);
    if (r0 == 0) {
        return;
    }
    func_0208affc((void *) r0);
}

void *func_0208affc(void *p)
{
    func_020ee660(p);
    *(void **) p = (void *) data_020da13c;
    *(void **) p = (void *) data_020e2288;
    return p;
}

void *func_0208afdc(volatile void *obj)
{
    *(volatile unsigned int *) obj = (unsigned int) data_020e2288;
    *(volatile unsigned int *) obj = (unsigned int) data_020da13c;
    func_020ee62c((void *) obj);
    return (void *) obj;
}

void *func_0208afb4(void *arg)
{
    *(int *) arg = (unsigned int) data_020e2288;
    *(int *) arg = (unsigned int) data_020da13c;
    func_020ee62c((void *) arg);
    func_020edf54(arg);
    return arg;
}

int func_0208af98(void)
{
    func_02003df0();
    func_02003a64();
    func_0208ee14();
    func_0208b55c();
    return 1;
}

int func_0208af7c(void)
{
    func_0208b54c();
    func_0208ee10();
    func_02003a54();
    func_02003de0();
    return 1;
}

int func_0208af60(void)
{
    func_02003dd0();
    func_02003a44();
    func_0208ee00();
    func_0208b53c();
    return 1;
}

int func_0208af44(void)
{
    func_02003a34();
    func_02003dc0();
    func_0208b52c();
    func_0208edf0();
    return 1;
}
