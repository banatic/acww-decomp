/* waiting_letter: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02090030 @ 0x02090030, 0x10 bytes, Thumb
 * func_02090020 @ 0x02090020, 0x10 bytes, Thumb
 * func_02090018 @ 0x02090018, 0x8 bytes, Thumb
 * func_02090000 @ 0x02090000, 0x18 bytes, Thumb
 * func_0208fff4 @ 0x0208fff4, 0xc bytes, Thumb
 * func_0208ffe8 @ 0x0208ffe8, 0xc bytes, Thumb
 * func_0208ffe4 @ 0x0208ffe4, 0x2 bytes, Thumb
 */

extern void func_02066694(int *);
extern void func_02066688(int arg);
extern void func_02066650(void *);
extern int func_02065ec0(unsigned char *);

void *func_02090030(void *arg)
{
    func_02066694(arg);
    return arg;
}

int func_02090020(int arg)
{
    func_02066688(arg);
    return arg;
}

void func_02090018(void *argument0)
{
    func_02066650((void *) argument0);
}

int func_02090000(unsigned char *argument0)
{
    int result;
    if (func_02065ec0((unsigned char *) argument0) != 0) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

void func_0208fff4(unsigned char *r0, unsigned char r1)
{
    r0[0x100] = r1;
}

unsigned char func_0208ffe8(unsigned char *param0)
{
    return param0[0x100];
}

void *func_0208ffe4(void *object)
{
    return object;
}
